#ifndef __TAG_HPP_
#define __TAG_HPP_

/*!
 * \file
 * This module provides tags for xml.
 * The base class \c tag is abstract, sub classes are
 * - \c tag_inner: can only hold more tag
 * - \c tag_data: can only hold data (string)
 *
 * \pre For all method, no pointer should NULL
 *
 * \author PASD
 * \date 2016
 */

#include <ostream>
#include <sstream>

#undef NDEBUG
#include <assert.h>

/*!
 * Abstract class for representing tags of XML.
 */
class Tag {
  /*! tag itself */
  std::string tag;

protected:
  Tag(std::string &_tag) : tag(_tag){};

public:
  std::string get_tag() { return tag; }
  virtual void print_open(std::ostream &out) { out << "<" << tag << ">\n"; }
  void print_close(std::ostream &out) { out << "</" << tag << ">\n"; }
  virtual bool accepts_sub_tag() = 0;
  virtual ~Tag() {}
};

/*!
 * Concrete class for Tag with sub-tag only.
 */
class Tag_Inner : public Tag {
public:
  Tag_Inner(std::string tag) : Tag(tag) {}
  bool accepts_sub_tag() { return true; }
  ~Tag_Inner(){};
};

/*!
 * Concrete class for Tag with data only.
 */
class Tag_Data : public Tag {
  std::string data;

public:
  Tag_Data(std::string tag, std::string _data) : Tag(tag), data(_data) {}
  std::string get_data() { return data; }
  bool accepts_sub_tag() { return false; }
  virtual void print_open(std::ostream &out) {
    Tag::print_open(out);
    out << data << "\n";
  }
  ~Tag_Data(){};
};

#endif
