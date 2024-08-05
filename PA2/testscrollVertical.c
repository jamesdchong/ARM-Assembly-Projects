/*
 * Filename: testscrollVertical.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for scrollVertical.c
 *
 * void scrollVertical( unsigned int pattern[], int offset );
 *
 * Scrolls pattern vertically based on the offset passed in
 */
void testscrollVertical() {

  unsigned int pattern[2] = { 0 };

  // Scroll Simple pattern
  pattern[0] = 0x1;
  pattern[1] = 0x0;

  scrollVertical( pattern, 1 );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x01000000 );

  // Scroll 0
  pattern[0] = 0x12345678;
  pattern[1] = 0x98765432;

  scrollVertical( pattern, 0 );

  TEST( pattern[0] == 0x12345678 );
  TEST( pattern[1] == 0x98765432 );

  // Test positive small offset
  pattern[0] = 0x12345678;
  pattern[1] = 0x98765432;

  scrollVertical( pattern, 1 );

  TEST( pattern[0] == 0x32123456 );
  TEST( pattern[1] == 0x78987654 );


  // Test negative small offset
  pattern[0] = 0x12345678;
  pattern[1] = 0x98765432;

  scrollVertical( pattern, -1 );

  TEST( pattern[0] == 0x34567898 );
  TEST( pattern[1] == 0x76543212 );

  // Test positive large offset
  pattern[0] = 0x12345678;
  pattern[1] = 0x98765432;

  scrollVertical( pattern, 78345 );

  TEST( pattern[0] == 0x32123456 );
  TEST( pattern[1] == 0x78987654 );

  // Test negative large offset
  pattern[0] = 0x12345678;
  pattern[1] = 0x98765432;

  scrollVertical( pattern, -79345 );

  TEST( pattern[0] == 0x34567898 );
  TEST( pattern[1] == 0x76543212 );

}

int main( void ) {

  fprintf( stderr, "Running tests for scrollVertical...\n" );
  testscrollVertical();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
