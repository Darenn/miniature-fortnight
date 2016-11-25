#include <fstream>
#include <string>

#include <iostream>

#include "xml.hpp"

#undef NDEBUG
#include <assert.h>

using namespace std;

void delete_Tag(Tag *&t) { delete t; }

namespace {

char const *const STR_SPC = " \t";

/*
 * Remove all trailing space at beginning and end.
 * \param str string to be trimmed.
 */
void trim(string &str) {
  // Left trim
  int i = 0;
  while (isspace(str[i])) {
    i++;
  };
  str.erase(0, i);
  // Right trim
  i = str.size();
  while (isspace(str[i])) {
    i--;
  }
  str.erase(i, str.size());
}

/*
 * Test if a trimmed string is an opening tag (of the form '<' then a letter
 * then letters and/or digits then '>')
 * If this is an opening tag, then the string is reduced to the letters and
 * digits.
 * \param str trimmed string.
 * \return true if this is an opening tag.
 */
bool is_opening_tag(string &str) {
  bool res = true;
  int i = 0;
  if (str[i++] != '<' || !isalpha(str[i++])) {
    res = false;
  }
  while (isalpha(str[i]) || isdigit(str[i])) {
    i++;
  }
  if (str[i++] != '>' || str[i] != 0) {
    res = false;
  }
  return res;
}

/*
 * Test if a trimmed string is an closing tag (of the form "</" then a letter
 * then letters and/or digits then '>')
 * If this is an closing tag, then the string is reduced to the letters and
 * digits.
 * \param str trimmed string.
 * \return true if this is an closing tag.
 */
bool is_closing_tag(string &str) {
  bool res = true;
  int i = 0;
  if (str[i++] != '<' || str[i++] != '/' || !isalpha(str[i++])) {
    res = false;
  }
  while (isalpha(str[i]) || isdigit(str[i])) {
    i++;
  }
  if (str[i++] != '>' || str[i] != 0) {
    res = false;
  }
  return res;
}

enum load_state {
  beginning,
  beginning_open,
  last_open_son,
  last_open_brother,
  last_data,
  last_close
};
}

#define FAIL_LOAD return NULL;

/*! This one comes with debugging outputs. */
#define TEST_TAG(lib1, lib2)                                                   \
  if ((lib1) != (lib2)) {                                                      \
    cerr << "ERROR " << *xml << endl;                                          \
    cerr << "tag " << (lib1) << " is closed by " << endl;                      \
    cerr << "tag " << (lib2) << endl;                                          \
    FAIL_LOAD;                                                                 \
  }

Xml *Xml::load(char const *const file_name) {
  ifstream file_stream(file_name);
  load_state state = beginning;
  string line;
  string last;

  Tree<Tag *, delete_Tag> *tree_ptr = NULL;
  Node<Tag *, delete_Tag> *node_current = NULL;

  while (getline(file_stream, line)) {
    trim(line);

    switch (state) {

    case beginning:
      if (is_opening_tag(line)) {
        state = beginning_open;
        line = line.substr(1, line.size() - 2);
      } else {
        FAIL_LOAD
      }
      break;

    case beginning_open:
      Tag *t;
      if (is_opening_tag(line)) {
        state = last_open_son;
        line = line.substr(1, line.size() - 2);
        t = new Tag_Inner(last);
      } else if (is_closing_tag(line)) {
        state = last_close;
        line = line.substr(2, line.size() - 2);
        t = new Tag_Inner(last);
      } else {
        state = last_data;
        t = new Tag_Data(last, line);
      }
      tree_ptr = new Tree<Tag *, delete_Tag>(t);
      node_current = (*tree_ptr).get_root();
      break;

    case last_open_son:
      if (is_opening_tag(line)) {
        state = last_open_son;
        line = line.substr(1, line.size() - 2);
        node_current = node_current->add_left_son(new Tag_Inner(last));
      } else if (is_closing_tag(line)) {
        state = last_close;
        line = line.substr(2, line.size() - 2);
        node_current = node_current->add_left_son(new Tag_Inner(last));
      } else {
        state = last_data;
        node_current = node_current->add_left_son(new Tag_Data(last, line));
      }
      break;

    case last_open_brother:
      if (is_opening_tag(line)) {
        state = last_open_son;
        line = line.substr(1, line.size() - 2);
        node_current = node_current->add_right_brother(new Tag_Inner(last));
      } else if (is_closing_tag(line)) {
        state = last_close;
        line = line.substr(2, line.size() - 2);
        node_current = node_current->add_right_brother(new Tag_Inner(last));
      } else {
        state = last_data;
        node_current =
            node_current->add_right_brother(new Tag_Data(last, line));
      }
      break;

    case last_data:
      if (is_closing_tag(line)) {
        state = last_close;
        line = line.substr(2, line.size() - 2);
      } else {
        FAIL_LOAD
      }
      break;

    case last_close:
      if (is_opening_tag(line)) {
        state = last_open_brother;
        line = line.substr(1, line.size() - 2);
        node_current = node_current->add_right_brother(new Tag_Inner(last));
      } else if (is_closing_tag(line)) {
        state = last_close;
        line = line.substr(2, line.size() - 2);
        node_current =
            node_current->add_right_brother(new Tag_Inner(last))->get_father();
      } else {
        FAIL_LOAD
      }
      break;
    }

    last = line;
  }

  file_stream.close();
  return new Xml(tree_ptr);
}

std::ostream &operator<<(std::ostream &out, Xml const &xml) {
  Node<Tag *, delete_Tag> *current = xml.tree->get_root();
  bool b = true;

  /*while (current != NULL) {
    if (b) {
      current->get_value()->print_open(cout);
    } else {
      current->get_value()->print_close(cout);
    }
    if (current->get_left_son() != NULL) {
      current = current->get_left_son();
      b = true;
    } else {
      if (current->get_right_brother() != NULL) {
        current = current->get_right_brother();
        b = !b;
      } else {
        current = current->get_father();
        b = false;
      }
    }
  }*/

  return cout << endl;
}
