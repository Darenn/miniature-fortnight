

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
void trim(string &str) {}

/*
 * Test if a trimmed string is an opening tag (of the form '<' then a letter
 * then letters and/or digits then '>')
 * If this is an opening tag, then the string is reduced to the letters and
 * digits.
 * \param str trimmed string.
 * \return true if this is an opening tag.
 */
bool is_opening_tag(string &str) { return true; }

/*
 * Test if a trimmed string is an closing tag (of the form "</" then a letter
 * then letters and/or digits then '>')
 * If this is an closing tag, then the string is reduced to the letters and
 * digits.
 * \param str trimmed string.
 * \return true if this is an closing tag.
 */
bool is_closing_tag(string &str) { return true; }

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

Xml *Xml::load(char const *const file_name) { return NULL; }

std::ostream &operator<<(std::ostream &out, Xml const &xml) { return out; }
