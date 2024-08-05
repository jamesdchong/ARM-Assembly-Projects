/*
 * Filename: testisDividable
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa1.h"
#include "test.h"

/*
 * Unit Test for isDividable.s
 *
 * int isDividable( int dividend, int divisor );
 *
 * Checks to see if division divides evenly or not
 *
 * Returns -1 if divisor is 0
 * Returns 0 if division does not divide evenly
 * Returns 1 if division divides evenly
 */
void testisDividable() {

  /* Test for dividable postive dividend and divisor */
  TEST( isDividable( 12, 4 ) == 1 );

  /* Test for undividable positive dividend and divisor */
  TEST( isDividable( 5, 3 ) == 0 );

  /* Test when divisor is 0 */
  TEST( isDividable( 10, 0 ) == -1 );

  /* Test dividable positive dividend, negative divisor */
  TEST( isDividable( 12, -4 ) == 1 );

  /* Test dividable negative dividend, positive divisor */
  TEST( isDividable(-12, 4 ) == 1 );

  /* Test undividable positive dividend, negative divisor */
  TEST( isDividable( 6, -5 ) == 0 );

  /* Test undividable negative dividend, positive divisor */
  TEST( isDividable( -6, 5 ) == 0 );

  /* Test dividable negative dividend and divisor */
  TEST( isDividable( -12, -4 ) == 1 );

  /* Test undividable negative dividend and divisor */
  TEST( isDividable( -6, -5 ) == 0 );

  /* Test dividend less than divisor */
  TEST( isDividable( 1, 4 ) == 0 );

  /* Test larger input values */
  TEST( isDividable( 23452346, 23452345 ) == 0 );

  /* Test decimal values */
  TEST( isDividable( 4.5, 3.6 ) == 0 );

}

int main( void ) {

  fprintf( stderr, "Running tests for isDividable...\n" );
  testisDividable();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
