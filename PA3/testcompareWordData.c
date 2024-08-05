/*
 * Filename: testcompareWordData.c
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
 * Unit Test for compareWordData.c
 *
 * int compareWordData( const void * w1, const void * w2 );
 *
 * Compares wordData_t pointers w1 and w2
 *
 * Returns -1 if:
 * 		       the wordData_t that w1 points to has a smaller hashValue
 * 		       than the wordData_t that w2 points to, or the hashValues
 * 		       are the same but strncmp returns a value < 0.
 * 		     1 if:
 * 		       the wordData_t that w1 points to has a larger hashValue than
 * 		       the wordData_t that w2 points to, or the hasValues are the
 * 		       same but strncmp returns a value > 0.
 * 	    	 0 if:
 * 		       the hashValues are the same and strncmp returns 0
 */
void testcompareWordData() {
  // Create 2 wordData_t
  wordData_t wordData0 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  wordData_t wordData1 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  const wordData_t * w0 = &wordData0;
  const wordData_t * w1 = &wordData1;

  // Test same words, same hashValues
  TEST( compareWordData( w0, w1 ) == 0 );

  // Test same wordData
  TEST( compareWordData( w0, w0 ) == 0 );

  // Create 2 wordData_t
  wordData_t wordData2 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 40
  };

  wordData_t wordData3 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  const wordData_t * w2 = &wordData2;
  const wordData_t * w3 = &wordData3;

  // Test same words, w1's hashValue greater than w2's hashValue
  TEST( compareWordData( w2, w3 ) == 1 );


  // Create 2 wordData_t
  wordData_t wordData4 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 10
  };

  wordData_t wordData5 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  const wordData_t * w4 = &wordData4;
  const wordData_t * w5 = &wordData5;

  // Test same words, w1's hashValue less than w2's hashValue
  TEST( compareWordData( w4, w5 ) == -1 );


  // Create 2 new wordData_t
  wordData_t wordData6 = {
    .word = { "hello" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  wordData_t wordData7 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  const wordData_t * w6 = &wordData6;
  const wordData_t * w7 = &wordData7;

  // Test same hashValues, but strncmp < 0
  TEST( compareWordData( w6, w7 ) == -1 );



  // Create 2 new wordData_t
  wordData_t wordData8 = {
    .word = { "hi" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  wordData_t wordData9 = {
    .word = { "hello" },
    .counts = { 30, 60, 90 },
    .hashValue = 20
  };

  const wordData_t * w8 = &wordData8;
  const wordData_t * w9 = &wordData9;

  // Test same hashValues, but strncmp > 0
  TEST( compareWordData( w8, w9 ) == 1 );

}

int main( void ) {

  fprintf( stderr, "Running tests for compareWordData...\n" );
  testcompareWordData();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
