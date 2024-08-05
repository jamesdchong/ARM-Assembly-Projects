/*
 * Filename: testoutputCharNTimes.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for outputCharNTimes.c
 *
 * void outputCharNTimes( char ch, int n );
 *
 * Prints the "ch" character "n" amount of times
 */
void testoutputCharNTimes() {

  /* Should print 'h' 3 times */
  outputCharNTimes( 'h', 3 );

  /* Should not print anyting */
  outputCharNTimes( 'k', -2 );

  /* Should print '&' 5 times */
  outputCharNTimes( '&', 5 );

  /* Should print '6' 3 times */
  outputCharNTimes( '6', 3 );

  /* Should print 'a' 1 times */
  outputCharNTimes( 'a', 1 );

  /* Should not print anything */
  outputCharNTimes( 'p', 0 );

  /* Print new line */
  outputChar( '\n' );

}

int main( void ) {

  fprintf( stderr, "Running tests for outputCharNTimes...\n" );
  testoutputCharNTimes();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
