/*
 * Filename: testintervalContains.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */ 

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for intervalContains.s
 *
 * int intervalContains( int start, int end, int value );
 *
 * Checks to see if the interval contains the value (inclusive on both ends).
 *
 * Returns -1 if start > end
 * Returns 1 if the interval contains the value
 * Returns 0 otherwise.
 */
void testintervalContains() {

  /* Test interval containing the value */
  TEST( intervalContains( 0, 2, 1 ) == 1 );

  /* Test interval containing the value */
  TEST( intervalContains( 0, 1, 0 ) == 1 );

  /* Test start greater than end */
  TEST( intervalContains( 2, 1, 0 ) == -1 );

  /* Test value less than start */
  TEST( intervalContains( 2, 4, 1 ) == 0 );

  /* Test value greater than end */
  TEST( intervalContains( 2, 4, 8 ) == 0 );

  /* Test negative interval */
  TEST( intervalContains( -4, -1, -2 ) == 1 );

  /* Test larger values */
  TEST( intervalContains( 23452345, 234523457, 234523456 ) == 1 );

  /* Test decimal values */
  TEST( intervalContains( 4.534, 8.243, 6.234 ) == 1 );

}


int main( void ) {

  fprintf( stderr, "Running tests for intervalContains...\n" );
  testintervalContains();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
