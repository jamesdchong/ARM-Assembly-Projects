/*
 * Filename: testmyURem.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/11/19
 * Sources of help: None
 */

#include <stdio.h>
#include <string.h>

#include "pa3.h"
#include "test.h"

/*
 * Unit Test for myURem.s
 *
 * unsigned int myURem( unsigned int dividend, unsigned int divisor );
 *
 * Calculates remainder of unsigned dividend by unsigned divisor
 *
 * Returns the remainder
 */
void testmyURem() {

  /* Test positive dividend and divisor */
  TEST( myURem( 6, 5 ) == 1 );

  /* Test positive dividend, negative divisor */
  TEST( myURem( 6, -5 ) == 6 );

  /* Test negative dividend, positive divisor */
  TEST( myURem( -6, 5 ) == 0 );

  /* Test negative dividend and divisor */
  TEST( myURem( -6, -5 ) == -6 );

  /* Test dividend that is zero */
  TEST( myURem( 0, 5 ) == 0 );

  /* Test larger input values */
  TEST( myURem( 23452346, 23452345 ) == 1 );

  /* Test decimal values */
  TEST( myURem( 4.5, 3.6 ) == 1 );

}

int main( void ) {

  fprintf( stderr, "Running tests for myURem...\n" );
  testmyURem();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
