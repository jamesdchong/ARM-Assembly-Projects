/*
 * Filename: testlineMatchesRegex.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/27/19
 * Sources of help: None
 */

#include <stdio.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for lineMatchesRegex.c
 *
 * int lineMatchesRegex( const regex_t * pattern, const char * line );
 *
 * Checks if line matches regex
 *
 * Returns 1 if line matches regex pattern, otherwise return 0
 */
void testlineMatchesRegex() {

  regex_t preg;
  int cflags = 0;

  // Test same words
  regcomp( &preg, "hi", cflags );

  TEST( lineMatchesRegex( &preg, "hi" ) == 1 );

  // Test different words
  regcomp( &preg, "hello", cflags );

  TEST( lineMatchesRegex( &preg, "hi" ) == 0 );

  // Test substring inside string
  regcomp( &preg, "abc", cflags );

  TEST( lineMatchesRegex( &preg, "abcde" ) == 1 );

  TEST( lineMatchesRegex( &preg, "deabc" ) == 1 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for lineMatchesRegex.c...\n" );
  testlineMatchesRegex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
