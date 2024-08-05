/*
 * Filename: testoutputChar.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for outputChar.s
 *
 * void outputChar( char ch );
 *
 * Prints out the char passed in
 */
void testoutputChar() {

  /* Should print 'e' */
  outputChar( 'e' );

  /* Should print '!' */
  outputChar( '!' );

  /* Should print '&' */
  outputChar( '&' );

  /* Should print '3' */
  outputChar( '3' );

  /* Should print 'A' */
  outputChar( 'A' );

  /* Prints a new line */
  outputChar( '\n' );

}


int main( void ) {

  fprintf( stderr, "Running tests for outputChar...\n" );
  testoutputChar();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
