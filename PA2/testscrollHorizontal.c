/*
 * Filename: testscrollHorizontal.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for scrollHorizontal.c
 *
 * void scrollHorizontal( unsigned int pattern[], const int offset );
 *
 * Scroll horizontally by offset.
 *    If offset is positive, shift bits right.
 *    If offset is negative, shift bits left.
 */
void testscrollHorizontal() {

  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Scroll Simple pattern
  pattern[0] = 0x1;
  pattern[1] = 0x0;

  scrollHorizontal( pattern, 1 );

  TEST( pattern[0] == 0x00000080 );
  TEST( pattern[1] == 0x00000000 );

  // Test offset = 0: shouldn't move
  pattern[0] = 0xAAAAAAAA;
  pattern[1] = 0xCCCCCCCC;

  scrollHorizontal( pattern, 0 );

  TEST( pattern[0] == 0xAAAAAAAA );
  TEST( pattern[1] == 0xCCCCCCCC );

  // Test offset = 4: should swap the nibbles in each byte
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0xCCCCCCCC;

  scrollHorizontal( pattern, 4 );

  TEST( pattern[0] == 0xBADCFE10 );
  TEST( pattern[1] == 0xCCCCCCCC );

  // Scroll positive small
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0x76543210;

  scrollHorizontal( pattern, 1 );

  TEST( pattern[0] == 0xD5E6F780 );
  TEST( pattern[1] == 0x3B2A1908 );

  // Scroll positive large
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0x76543210;

  scrollHorizontal( pattern, 2 );

  TEST( pattern[0] == 0xEA73FB40 );
  TEST( pattern[1] == 0x9D158C04 );

  // Scroll negative small
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0x76543210;

  scrollHorizontal( pattern, -1 );

  TEST( pattern[0] == 0x579BDF02 );
  TEST( pattern[1] == 0xECA86420 );

  // Scroll negative large
  pattern[0] = 0xABCDEF01;
  pattern[1] = 0x76543210;

  scrollHorizontal( pattern, -2 );

  TEST( pattern[0] == 0xAE37BF04);
  TEST( pattern[1] == 0xD951C840 );

}

int main( void ) {

  fprintf( stderr, "Running tests for scrollHorizontal...\n" );
  testscrollHorizontal();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
