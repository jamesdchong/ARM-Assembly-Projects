/*
 * Filename: testcomputeHash.c
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
 * Unit Test for computeHash.c
 *
 * int computeHash( const char * str );
 *
 * Creates and returns a hash value based on the string passed in.
 *
 * Returns the hash value of str
 */
void testcomputeHash() {

  // Test one lowercase letter
  char str0[] = "h";
  
  TEST( computeHash( str0 ) == 507 );

  // Test one uppercase letter
  char str1[] = "Z";
  
  TEST( computeHash( str1 ) == 493 );
  
  // Test larger lowercase string
  char str2[] = "abcdef";

  TEST( computeHash( str2 ) == 1523227312 );

  // Test larger uppercase string
  char str3[] = "ABCDEF";

  TEST( computeHash( str3 ) == 576556720 );

  // Test one number
  char str4[] = "9";

  TEST( computeHash( str4 ) == 460 );

  // Test many numbers
  char str5[] = "12345";

  TEST( computeHash( str5 ) == 418971718 );

  // Test symbols
  char str6[] = "!@#$%";

  TEST( computeHash( str6 ) == 404596568 );

  // Test combination of lowercase, uppercase letters, numbers, and symbols
  char str7[] = "hello!*73hi2&^";

  TEST( computeHash( str7 ) == 1231073055 );

}

int main( void ) {

  fprintf( stderr, "Running tests for computeHash...\n" );
  testcomputeHash();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
