/*
 * Filename: testcharacter.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for character.c
 *
 * void character( unsigned int pattern[], char ch,
 *                 const char * alphabetPatterns[],
 *                 const char * digitPatterns[] );
 *
 * Fills pattern array with bit patterns of specified letter or number
 * 
 * Returns -1 if ch is not a letter or a number
 * Returns 0 otherwise
 */
void testcharacter() {

  unsigned int pattern[2] = { 0 };
  const char * letters[] = ALPHABET_PATTERNS;
  const char * digits[] = DIGIT_PATTERNS;

  /* Test capital letter */
  TEST( character( pattern, 'A', letters, digits ) == 0 );

  /* Test lowercase letter */
  TEST( character( pattern, 'a', letters, digits ) == 0 );

  /* Test last letter */
  TEST( character( pattern, 'z', letters, digits ) == 0 );

  /* Test non-alphanumeric character */
  TEST( character( pattern, '&', letters, digits ) == -1 );

  /* Test number greater than 9 */
  TEST( character( pattern, 10, letters, digits ) == -1 );

  /* Test number less than 0 */
  TEST( character( pattern, -1, letters, digits ) == -1 );

  /* Test number in single quotes */
  TEST( character( pattern, '3', letters, digits ) == 0 );

  /* Test 0 (first element of valid interval) */
  TEST( character( pattern, '0', letters, digits ) == 0 );

  /* Test 0 (last element of valid interval) */
  TEST( character( pattern, '9', letters, digits ) == 0 );

  /* Test integer without single quotes */
  TEST( character( pattern, 5, letters, digits ) == -1 );

}

int main( void ) {

  fprintf( stderr, "Running tests for character...\n" );
  testcharacter();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
