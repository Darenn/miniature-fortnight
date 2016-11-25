#ifndef __XML_HPP_
#define __XML_HPP_

/*!
 * \file
 * This module provides a class for recording xml documents.
 *
 * \author PASD
 * \date 2016
 */

#include "tag.hpp"
#include "tree.hpp"

#undef NDEBUG
#include <assert.h>

/*!
 * For template instantiation.
 */
extern void delete_Tag(Tag *&t);

/*!
 * This class records Xml documents as Tree of Tag.
 */
class Xml {

  Tree<Tag *, delete_Tag> *tree;

  Xml(Tree<Tag *, delete_Tag> *tree) : tree(tree){};

public:
  static Xml *load(char const *const file_name);

  ~Xml() { delete tree; }

  friend std::ostream &operator<<(std::ostream &out, Xml const &xml);
};

/*!
 * Output a Xml tree on a stream, like for example:
 * \verbatim
<racine>
<fille>
<petiteFille>
BBBB ! : , b fg
</petiteFille>
<petiteFilleAutre>
34567890  LKJHGFDS
</petiteFilleAutre>
</fille>
</racine>
 * \endverbatim
 * \param xml The xml to  output.
 * \return the output stream \c out.
 */
std::ostream &operator<<(std::ostream &out, Xml const &xml);

#endif
