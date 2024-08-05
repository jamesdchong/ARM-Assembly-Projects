/*
 * Filename: testloadPatternString.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for loadPatternString.c
 *
 * void loadPatternString( unsigned int pattern[], const char * patternStr );
 *
 * Goes through each character in patternStr and sets bits in pattern to be
 * on or off, depending on its value
 */
void testloadPatternString() {

  unsigned int pattern[2] = { 0 };

  // Test all on
  loadPatternString( pattern,
  "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" );

  TEST( pattern[0] == 0xFFFFFFFF );
  TEST( pattern[1] == 0xFFFFFFFF );

  // Test all off
  loadPatternString( pattern,
  "----------------------------------------------------------------" );

  TEST( pattern[0] == 0x00000000 );
  TEST( pattern[1] == 0x00000000 );

  // Test edges on
  loadPatternString( pattern,
  "@--------------------------------------------------------------@" );

  TEST( pattern[0] == 0x80000000 );
  TEST( pattern[1] == 0x00000001 );

  // Test middle two on others off
  loadPatternString( pattern,
  "-------------------------------@@-------------------------------" );

  TEST( pattern[0] == 0x00000001 );
  TEST( pattern[1] == 0x80000000 );
  
  // Test alternating
  loadPatternString( pattern,
  "@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-@-" );

  TEST( pattern[0] == 0xAAAAAAAA );
  TEST( pattern[1] == 0xAAAAAAAA );

  // Test "Z" string
  loadPatternString( pattern,
  "---------@@@@@@------@------@------@------@------@@@@@@---------" );

  TEST( pattern[0] == 0x007E0408 );
  TEST( pattern[1] == 0x10207E00);

  // Test "0" string
  loadPatternString( pattern,
  "----------@@@@---@---@@--@--@-@--@-@--@--@@---@---@@@@----------" );

  TEST( pattern[0] == 0x003C464A );
  TEST( pattern[1] == 0x52623C00 );


  // Test "9" string
  loadPatternString( pattern,
  "----------@@@@---@----@--@----@---@@@@@-------@---@@@@----------" );

  TEST( pattern[0] == 0x003C4242 );
  TEST( pattern[1] == 0x3E023C00 );


  // Test "A" string
    loadPatternString( pattern,
  "---------@@@@@@--@----@--@----@--@@@@@@--@----@--@----@---------" );
  TEST( pattern[0] == 0x007E4242 );
  TEST( pattern[1] == 0x7E424200 );
  
}

int main( void ) {

  fprintf( stderr, "Running tests for loadPatternString...\n" );
  testloadPatternString();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
