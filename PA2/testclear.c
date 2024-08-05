/*
 * Filename: testclear.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for clear.c
 *
 * void clear( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Turns off bits in pattern with bits in part0 and part1
 *   If bit value in part0 or part1 is 1, then corresponding bit in pattern is 0
 *   If bit value in part0 or part1 is 0, then corresponding bit in pattern
 *     remains the same
 */
void testclear() {

  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup case
  pattern[0] = 0xFF00FF00;
  pattern[1] = 0xAAAAAAAA;

  clear( pattern, 0xFF000000, 0x88888888 );

  TEST( pattern[0] == 0x0000FF00 );
  TEST( pattern[1] == 0x22222222 );

  // Test all 1's in part0 and no 1's in part1
  pattern[0] = 0xA758EF22;
  pattern[1] = 0xB73F1240;

  clear( pattern, 0xFFFFFFFF, 0x67829387 );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x903D0040 );

  // Test all 0's in part0 and part1
  pattern[0] = 0xA9837482;
  pattern[1] = 0x01749382;

  clear( pattern, 0x00000000, 0x00000000 );

  TEST( pattern[0] == 0xA9837482 );
  TEST( pattern[1] == 0x01749382 );

  // Test all 1's in pattern[0] and no 1's in pattern[1]
  pattern[0] = 0xFFFFFFFF;
  pattern[1] = 0x71938472;

  clear( pattern, 0x72049573, 0x71958473 );

  TEST( pattern[0] == 0x8DFB6A8C );
  TEST( pattern[1] == 0x00020000 );
  
  // Test all 0's in pattern[0] and pattern[1]
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;

  clear( pattern, 0x72049573, 0x71958473 );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x00000000 );

}

int main( void ) {

  fprintf( stderr, "Running tests for clear...\n" );
  testclear();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
