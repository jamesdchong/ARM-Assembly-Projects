/*
 * Filename: testmyRem.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for myRem.s
 *
 * int myRem( int dividend, int divisor );
 *
 * Calculates the remainder of dividing the dividend by the divisor
 *
 * Returns the remainder of the division
 */
void testmyRem() {

  /* Test positive dividend and divisor */
  TEST( myRem( 6, 5 ) == 1 );

  /* Test positive dividend, negative divisor */
  TEST( myRem( 6, -5 ) == 1 );

  /* Test negative dividend, positive divisor */
  TEST( myRem( -6, 5 ) == -1 );

  /* Test negative dividend and divisor */
  TEST( myRem( -6, -5 ) == -1 );

  /* Test dividend that is zero */
  TEST( myRem( 0, 5 ) == 0 );

  /* Test larger input values */
  TEST( myRem( 23452346, 23452345 ) == 1 );

  /* Test decimal values */
  TEST( myRem( 4.5, 3.6 ) == 1 );

}


int main( void ) {

  fprintf( stderr, "Running tests for myRem...\n" );
  testmyRem();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
