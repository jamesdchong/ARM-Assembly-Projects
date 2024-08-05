/*
 * Filename: testset.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for testset.c
 *
 * void set( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Turns on bits in pattern with bits in part0 and part1
 *  If bit value in part0 or part1 is 1, then corresponding bit in pattern is 1
 *  If bit value in part0 or part1 is 0, then corresponding bit in patterns
 *    remains the same
 * 
 */
void testset() {

  unsigned int pattern[PATTERN_LEN] = { 0 };
  
  // Test writeup case
  pattern[0] = 0x00100001;
  pattern[1] = 0x01F00F001;

  set( pattern, 0x420C5E30, 0xF001F008 );

  TEST( pattern[0] == 0x421C5E31 );
  TEST( pattern[1] == 0xFF01F009 );

  // Test all ones
  pattern[0] = 0x11111111;
  pattern[1] = 0x11111111;

  set( pattern, 0x11111111, 0x11111111 );

  TEST( pattern[0] = 0x11111111 );
  TEST( pattern[1] = 0x11111111 );

  // Test with no zeros or ones
  pattern[0] = 0x78492874;
  pattern[1] = 0xA9275849;

  set( pattern, 0xF8629473, 0x81047C38 );

  TEST( pattern[0] = 0xF8629473 );
  TEST( pattern[1] = 0x81047C38 );

  // Test same pattern[0] with part0 and same pattern[1] with part
  pattern[0] = 0x00100001;
  pattern[1] = 0x01F00F001;

  set( pattern, 0x00100001, 0x01F00F001 );

  TEST( pattern[0] == 0x00100001 );
  TEST( pattern[1] == 0x01F00F001 );

  // Test all zeros
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;

  set( pattern, 0x00000000, 0x00000000 );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x00000000 );

  // Test half ones
  pattern[0] = 0x11110000;
  pattern[1] = 0x11110000;

  set( pattern, 0x11110000, 0x11110000 );

  TEST( pattern[0] = 0x11110000 );
  TEST( pattern[1] = 0x11110000 );

}

int main( void ) {

  fprintf( stderr, "Running tests for set...\n" );
  testset();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
