/*
 * Filename: testtoggle.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for toggle.c
 *
 * void set( unsigned int pattern[], unsigned int part0, unsigned int part1 );
 *
 * Toggles all bits in pattern specified in part0 and part1
 *   If bit value in part0 or part1 is 1, then corresponding bit inverts
 *   If bit value in part0 or part1 is 0, then corresponding bit remains same
 */
void testtoggle() {

  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Test writeup case
  pattern[0] = 0xCAFEBABE;
  pattern[1] = 0xDECAFBAD;

  toggle( pattern, 0x420C5E30, 0xDEADBEEF );

  TEST( pattern[0] == 0x88F2E48E );
  TEST( pattern[1] == 0x00674542 );

  // Test all 0's in part0 and part1
  pattern[0] = 0x70193473;
  pattern[1] = 0x73920192;

  toggle( pattern, 0x00000000, 0x0000000 );

  TEST( pattern[0] == 0x70193473 );
  TEST( pattern[1] == 0x73920192 );

  // Test all 1's in part0 and part1
  pattern[0] = 0x70193473;
  pattern[1] = 0x73920192;

  toggle( pattern, 0xFFFFFFFF, 0xFFFFFFFF );

  TEST( pattern[0] == 0x8FE6CB8C );
  TEST( pattern[1] == 0x8C6DFE6D );
  
  // Test all 0's in pattern[0] and pattern[1]
  pattern[0] = 0x00000000;
  pattern[1] = 0x00000000;

  toggle( pattern, 0x72049574, 0x74937593 );

  TEST( pattern[0] == 0x72049574 );
  TEST( pattern[1] == 0x74937593 );

  // Test all 1's in pattern[0] and pattern[1]
  pattern[0] = 0xFFFFFFFF;
  pattern[1] = 0xFFFFFFFF;

  toggle( pattern, 0x74957203, 0x74957204 );

  TEST( pattern[0] == 0x8B6A8DFC );
  TEST( pattern[1] == 0x8B6A8DFB ); 

}

int main( void ) {

  fprintf( stderr, "Running tests for toggle...\n" );
  testtoggle();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
