/*
 * Filename: testaddWordCount.c
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
 * Unit Test for addWordCount.c
 *
 * int addWordCount( tableSlot_t * slot, const char * word,
 *                   unsigned int decade, unsigned int count );
 *
 * Increments the corresponding word's decade's count by the count parameter.
 *
 * If the slot does not have a wordData_t struct for the word, then reallocates
 * space for another in the wordDataPtr. Otherwise, just increments the
 * decade's index in the counts array of the existing struct.
 *
 * Returns -1 on memory allocation error, otherwise returns 0.
 */
void testaddWordCount() {
  // Initialize an empty slot.
  tableSlot_t slot = {
    .wordDataPtr = NULL,
    .numWords = 0
  };

  const char * word;
  unsigned int decade;
  unsigned int decadeIdx;
  unsigned int count;

  // Adding word to an empty slot.
  word = "hello";
  decade = 1820;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 420;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 1 );
  TEST( strncmp( slot.wordDataPtr[0].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[0].counts[decadeIdx] == count );

  // Adding a new word, should resize the array.
  // "apple" sorted into index 0 before "hello" due to compareWordData.
  word = "apple";
  decade = 1800;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 1;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 2 );
  TEST( strncmp( slot.wordDataPtr[0].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[0].counts[decadeIdx] == count );


  // Adding same word should update count
  word = "hello";
  decade = 1820;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 10;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 2 );
  TEST( strncmp( slot.wordDataPtr[1].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[1].counts[decadeIdx] == 430 );

  // Add new word, in the correct, sorted order in before "apple", "hello"
  word = "good";
  decade = 2000;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 30;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 3 );
  TEST( strncmp( slot.wordDataPtr[0].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[0].counts[decadeIdx] == count );

  // Add another string
  word = "cse30";
  decade = 1940;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 100;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 4 );
  TEST( strncmp( slot.wordDataPtr[2].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[2].counts[decadeIdx] == count );

}

int main( void ) {

  fprintf( stderr, "Running tests for addWordCount.c...\n" );
  testaddWordCount();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
