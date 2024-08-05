/*
 * Filename: testlineShouldBePrinted.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/28/19
 * Sources of help: None
 */

#include <stdio.h>
#include <string.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for lineShouldBePrinted.c
 *
 * int lineShouldBePrinted( const char * line, const argInfo_t * info );
 *
 * Checks if line should be printed in search()
 *
 * Returns 1 if line should be printed, else 0
 */
void testlineShouldBePrinted() {

  argInfo_t info;

  regex_t preg;
  int cflags = 0;

  // Test same words
  memset( &info, 0, sizeof(argInfo_t) );

  regcomp( &preg, "hi", cflags );
  info.pattern = preg;

  TEST( lineShouldBePrinted( "hi", &info ) == 1 );

  // Test same words, -v flag set
  memset( &info, 0, sizeof(argInfo_t) );
  cflags = ARG_V_FLAG;

  regcomp( &preg, "hi", cflags );
  info.pattern = preg;
  info.flags = cflags;

  TEST( lineShouldBePrinted( "hi", &info ) == 0 );

  // Test different words
  memset( &info, 0, sizeof(argInfo_t) );
  cflags = 0;

  regcomp( &preg, "hello", cflags );
  info.pattern = preg;
  info.flags = cflags;

  TEST( lineShouldBePrinted( "hi", &info ) == 0 );

  // Test different words, -v flag set
  memset( &info, 0, sizeof(argInfo_t) );
  cflags = ARG_V_FLAG;

  regcomp( &preg, "hello", cflags );
  info.pattern = preg;
  info.flags = cflags;

  TEST( lineShouldBePrinted( "hi", &info ) == 1 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineShouldBePrinted.c...\n" );
  testlineShouldBePrinted();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
