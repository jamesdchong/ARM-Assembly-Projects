/*
 * Filename: testfindSlotIndex.c
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
 * Unit Test for findSlotIndex.c
 *
 * int findSlotIndex( const char * wordStr, size_t numSlots );
 *
 * Calculates the index into the slot array for the string wordStr in slot array
 * of size numSlots
 *
 * Returns index of wordStr in slot array
 */
void testfindSlotIndex() {

  // Test lowercase letter, small numSlot
  char str0[] = "h";

  TEST( findSlotIndex( str0, 10 ) == 7 );

  // Test lowercase letter, large numSlot
  char str1[] = "h";

  TEST( findSlotIndex( str1, 100 ) == 7 );

  // Test uppercase letter, small numSlot
  char str2[] = "Z";

  TEST( findSlotIndex( str2, 10 ) == 3 );

  // Test uppercase letter, large numSlot
  char str3[] = "Z";

  TEST( findSlotIndex( str3, 100 ) == 93 );

  // Test larger lowercase string, small numSlot
  char str4[] = "abcdef";

  TEST( findSlotIndex( str4, 10 ) == 2 );

  // Test larger lowercase string, large numSlot
  char str5[] = "abcdef";;

  TEST( findSlotIndex( str5, 100 ) == 12 );

  // Test larger uppercase string, small numSlot
  char str6[] = "ABCDEF";

  TEST( findSlotIndex( str6, 10 ) == 0 );

  // Test larger upperca1se string, large numSlot
  char str7[] = "ABCDEF";

  TEST( findSlotIndex( str7, 100 ) == 20 );

  // Test number, small numSlot
  char str8[] = "9";

  TEST( findSlotIndex( str8, 10 ) == 0 );

  // Test number, large numSlot
  char str9[] = "9";

  TEST( findSlotIndex( str9, 100 ) == 60 );

  // Test many numbers, small numSlot
  char str10[] = "12345";

  TEST( findSlotIndex( str10, 10 ) == 8 );

  // Test many numbers, large numSlot
  char str11[] = "12345";

  TEST( findSlotIndex( str11, 100 ) == 18 );

  // Test symbols, small numSlot
  char str12[] = "!@#$%";

  TEST( findSlotIndex( str12, 10 ) == 8 );

  // Test symbols, large numSlot
  char str13[] = "!@#$%";

  TEST( findSlotIndex( str13, 100 ) == 68 );

  // Test combination of lowercase, uppercase letters, numbers, symbols
  char str14[] = "hello!*73hi2&^";

  TEST( findSlotIndex( str14, 10 ) == 5 );

  // Test 0 numSlot
  char str15[] = "h";

  TEST( findSlotIndex( str15, 0 ) == 507 );

  // Test small negative numSlot
  char str16[] = "h";

  TEST( findSlotIndex( str16, -10 ) == 507 );

  // Test large negative numSlot
  char str17[] = "h";

  TEST( findSlotIndex( str17, -100 ) == 507 );

}

int main( void ) {

  fprintf( stderr, "Running tests for findSlotIndex...\n" );
  testfindSlotIndex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
