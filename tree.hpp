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

#define DELETE_NOT delete_not<T>

template <class T, void (*delete_T)(T &) = DELETE_NOT> class Node {

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
  Node *add_left_son(T val) {
    Node *son = new Node(val, this);
    if (left_son != NULL) {
      son->right_brother = left_son;
    }
    left_son = son;
    return son;
  }

  /*! To add a brother to the right (to the left of any other existing son).
   * \param val Value for the added brother.
   * \return A pointer to the newly created \c Node.
   */
  Node *add_right_brother(T val) {
    Node *n = new Node(val, father);
    if (right_brother != NULL) {
      n->right_brother = right_brother;
    }
    right_brother = n;
    return n;
  }

  /*!
   * Destructor.
   */
  ~Node() {
    delete_T(value);
    Node *toDestroy = left_son;
    Node *nextToDestroy;
    while (toDestroy != NULL) {
      nextToDestroy = toDestroy->right_brother;
      delete (toDestroy);
      toDestroy = nextToDestroy;
    }
  };

  void output(std::ostream &ost, char const *const open_sons,
              char const *const sep_brothers, char const *const close_sons) {
    ost << value;
    if (left_son != NULL) {
      ost << open_sons;
      left_son->output(ost, open_sons, sep_brothers, close_sons);
      ost << close_sons;
    }
    if (right_brother != NULL) {
      ost << sep_brothers;
      right_brother->output(ost, open_sons, sep_brothers, close_sons);
    }
  }
};

/*!
 * This class is to represent a tree.
 * \param T Type for nodes.
 * \param delete_T function to delete the value of type T.
 */
template <class T, void (*delete_T)(T &) = DELETE_NOT> class Tree {

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
  ~Tree() { delete root; }

  template <char const *const open_sons, char const *const sep_brothers,
            char const *const close_sons>
  std::ostream &out_put(std::ostream &ost);
};

/*!
 * \brief Display the current tree into the given ostream.
 * \param T Type of the values in the tree.
 * \param delete_T Function to delete the value of type T.
 * \param open_sons String to begin sons display.
 * \param close_sons String to end sons display.
 * \param sep_brothers String to separe brothers.
 * \return the ostream given.
 */
template <class T, void (*delete_T)(T &)>
template <char const *const open_sons, char const *const sep_brothers,
          char const *const close_sons>
std::ostream &Tree<T, delete_T>::out_put(std::ostream &ost) {
  root->output(ost, open_sons, sep_brothers, close_sons);
  return ost;
}

#endif
