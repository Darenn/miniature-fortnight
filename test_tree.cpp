/*!
 * \file 
 * This module provides tests for the generic classes for unbouded trees.
 *
 * \author PASD
 * \date 2016
 */

# include <math.h>
# include <iostream>
# include <stdlib.h>

# include "tree.hpp"


# undef NDEBUG
# include <assert.h>


using namespace std ; 

namespace {

  int const size = 15 ;

  /*! Opening parenthesis for example.
   * Have to be declared as extern and array to be a template char cont * parameter. */
  extern char const open_sons_parent [] = " ( " ;
  /*! Separator between brothers for example.
   * Have to be declared as extern and array to be a template char cont * parameter. */
  extern char const sep_brothers_comma [] = " , " ;
  /*! Closing parenthesis for example.
   * Have to be declared as extern and array to be a template char cont * parameter. */
  extern char const close_sons_parent [] = " )" ;


  /*!
   * Class for representing complex numbers.
   */
  class Complex {

    float a ; 
    float b ; 
 
  public:
    Complex ( float _a ,
	      float _b )
      : a ( _a ) ,
	b ( _b ) {} ;
  
    Complex ( Complex const & c )
      : a ( c . a ) ,
	b ( c . b ) {} ; 

    ~Complex () {} ; 
    friend ostream & operator << ( ostream & ost ,
				   Complex const & c ) ; 
    friend ostream & operator << ( ostream & ost ,
				   Complex const * const & c ) ;
  } ; 


  ostream & operator << ( ostream & ost ,
			  Complex const & c ) 
  {
    ost << "[" << c . a << "," << c . b << "]" ; 
    return ost ; 
  } 

  ostream & operator << ( ostream & ost ,
			  Complex const * const & c ) 
  {
    ost << "[" << c -> a << "," << c -> b << "]p" ; 
    return ost ; 
  } 


  /*!
   * ¿¿¿ ???
   */
  void delete_complex ( Complex * & c ) {
    delete c ;
  }



# define MY_RAND_MAX 32767

  /* RAND_MAX assumed to be 32767 */
 
  int my_rand(void) {
    static unsigned long next = 123 ;
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % 32768);
  }

}



/*!
 * Add various nodes to a tree
 */
int main () {
  Complex ch ( 1.0 , 1.0 ) ; 
  Tree < Complex > tree ( ch ) ; 
  Node < Complex > * node_current = tree . get_root () ; 
  node_current = node_current -> add_left_son ( ch ) ;
  Tree < Complex * , delete_complex > tree_ptr ( new Complex ( ch ) ) ; 
  Node < Complex * , delete_complex > * node_ptr_current = tree_ptr . get_root () ; 
  node_ptr_current = node_ptr_current -> add_left_son ( new Complex ( ch ) ) ;
  for ( int i=0 ; i < size ; i++ ) {
    float a = ( float ) my_rand () / ( float ) MY_RAND_MAX ; 
    float b = ( float ) my_rand () / ( float ) MY_RAND_MAX ; 
    Complex c ( a , b ) ; 
    cout << c << endl ; 
    if ( i % 3 ==0 ) {
      node_current -> add_left_son ( c ) ; 
      node_ptr_current -> add_left_son ( new Complex ( c ) ) ; 
    } else if ( i % 2 ==0 ) {
      ( node_current -> get_right_brother () ) -> add_left_son ( c ) ; 
      ( node_ptr_current -> get_right_brother () ) -> add_left_son ( new Complex ( c ) ) ; 
    } else if ( i % 5 ==0 ) {
      node_current = node_current -> get_left_son () ;
    } else {
      node_current -> add_right_brother ( c ) ; 
      node_ptr_current -> add_right_brother ( new Complex ( c ) ) ; 
    }
  }
  tree . out_put < open_sons_parent , sep_brothers_comma , close_sons_parent > ( cout ) ;
  cout << endl ; 
  tree_ptr . out_put < open_sons_parent , sep_brothers_comma , close_sons_parent > ( cout ) ;
  cout << endl ; 

  return 0 ; 
}
 

