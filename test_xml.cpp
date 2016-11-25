/*!
 * \file 
 * This module provides tests for the xml module.
 *
 * \author PASD
 * \date 2016
 */


# include <iostream>

# include "xml.hpp"


# undef NDEBUG
# include <assert.h>


using namespace std ; 


/*!
 * Read a Xml in a file and the print it.
 */

void test_file ( char const * const file_name ) {
  Xml * xml = Xml :: load ( file_name ) ;
  cout << * xml ;
  delete xml ;
  cout << "----------------" << endl ;
}



/*!
 * Make the test with various Xml files.
 */

int main () {
  test_file ( "example_1.xml" ) ;
  test_file ( "example_2.xml" ) ;
  test_file ( "example_3.xml" ) ;
  test_file ( "example_4.xml" ) ;
  test_file ( "example_5.xml" ) ;  
  test_file ( "example_6.xml" ) ;
  test_file ( "example_7.xml" ) ;  
  return 0 ; 
}
 

