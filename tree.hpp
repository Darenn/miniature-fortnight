#ifndef __TREE_HPP_
#define __TREE_HPP_

/*!
 * \file
 * This module provides generic classes for unbouded trees.
 *
 * \author PASD
 * \date 2016
 */

#include <ostream>

#undef NDEBUG
#include <assert.h>

/*!
 * Template to generate default for second parameter of \c Node and \c Tree.
 * It does nothing.
 */
template <class T> void delete_not(T &) {}

/*!
 * This class encodes the nodes and their relative links.
 * \param T Type for nodes.
 * \param delete_T function to delete the value of type T.
 */
template <class T, void (*delete_T)(T &) = delete_not<T>> class Node {

  /*! Value held. */
  T value;
  /*! Link to the father.
   * Father cannot be changed!
   */
  Node *const father;
  /*! Link to the leftmost son. */
  Node *left_son;
  /*! Link to the leftmost right brother. */
  Node *right_brother;

public:
  /*!
   * Constructor.
   * A node must have a father, brothers and sons will come after.
   * \param val value to hold.
   * \param father link to the father node.
   */
  Node(T val, Node *father)
      : value(val), father(father), left_son(NULL), right_brother(NULL){};

  /*!
   * To get access to left son.
   * It can be used on const Node.
   * \return the value of \c left_son .
   */
  Node *get_left_son() const { return left_son; }

  /*!
   * To get access to right_brother.
   * It can be used on const Node.
   * \return the value of \c right_brother .
   */
  Node *get_right_brother() const { return right_brother; }

  /*!
   * To get access to the father.
   * It can be used on const Node.
   * \return the value of \c father .
   */
  Node *get_father() const { return father; }

  /*!
   * To get access to the value of \c val.
   * It can be used on const Node.
   * \return the value of \c val .
   */
  T get_value() const { return value; }

  /*! To add a left_son (to the left of any other existing son).
   * \param val Value for the added son.
   * \return A pointer to the newly created \c Node.
   */
  Node *add_left_son(T val) { return new Node(val, this); }

  /*! To add a brother to the right (to the left of any other existing son).
   * \param val Value for the added brother.
   * \return A pointer to the newly created \c Node.
   */
  Node *add_right_brother(T val) {
    return new Node(val, this->father->right_brother);
  }

  /*!
   * Destructor.
   * TODO should i destroy childrens ?
   */
  ~Node() {
    delete_T(value);
    delete (left_son);
  };
};

/*!
 * This class is to represent a tree.
 * \param T Type for nodes.
 * \param delete_T function to delete the value of type T.
 */
template <class T, void (*delete_T)(T &) = delete_not<T>> class Tree {

  /*
   * Root note of the tree.
   */
  Node<T, delete_T> *root;

public:
  /*
   * A tree is built from its root value.
   * Otherwise it cannot be build.
   * In particular, there is no empty tree.
   * \val val Value for the root note.
   */
  Tree(T const &val) : root(new Node<T, delete_T>(val, NULL)){};

  /*!
   * \return a pointer to the \c root Node.
   */
  Node<T, delete_T> *get_root() { return root; };

  /*!
   * Const version.
   * \return a pointer to the \c root Node.
   */
  Node<T, delete_T> const *get_root() const { return root; };

  /*!
   * Destructor.
   */
  ~Tree() {}

  template <char const *const open_sons, char const *const sep_brothers,
            char const *const close_sons>
  std::ostream &out_put(std::ostream &ost);
};

/*
 * ???
 */
template <class T, void (*delete_T)(T &)>
template <char const *const open_sons, char const *const sep_brothers,
          char const *const close_sons>
std::ostream &Tree<T, delete_T>::out_put(std::ostream &ost) {
  return ost;
}

#endif
