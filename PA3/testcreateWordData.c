/*
 * Filename: testcreateWordData.c
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
 * Unit Test for createWordData.c
 *
 * void createWordData( wordData_t * wordData, const char * wordStr,
 *                      unsigned int decade, unsigned int count );
 * 
 * Populates fields of wordData struct to represent the word in wordStr
 *
 */
void testcreateWordData() {
  // Create wordData
  wordData_t wordData = {
    .word = { 0 },
    .counts = { 0 },
    .hashValue = 0
  };

  wordData_t * w0 = &wordData;

  // Test simple create
  createWordData( w0,
  "hello", 1900, 30 );

  TEST( strncmp( wordData.word, "hello", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[10] == 30 );
  TEST( wordData.hashValue == 471341285 );

  // Test adding to 1800 decade
  createWordData( w0, "hello", 1800, 20 );

  TEST( strncmp( wordData.word, "hello", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[0] == 20 );
  TEST( wordData.hashValue == 471341285 );

  // Test adding to 2000 decade
  createWordData( w0, "hi", 2000, 10 );

  TEST( strncmp( wordData.word, "hi", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[20] == 10 );
  TEST( wordData.hashValue == 15822 );

  // Test empty string
  createWordData( w0, " ", 2000, 200 );

  TEST( strncmp( wordData.word, " ", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[20] == 200 );
  TEST( wordData.hashValue == 435 );

  // Test large string
  createWordData( w0, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                  2000, 50);

  TEST( strncmp( wordData.word,
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[20] == 50 );
  TEST( wordData.hashValue == 1566139860 );

  // Test large count
  createWordData( w0, "hello", 2000, 123456789 );

  TEST( strncmp( wordData.word, "hello", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[20] == 123456789 );
  TEST( wordData.hashValue == 471341285 );

  // Test small count
  createWordData( w0, "hello", 2000, 0 );

  TEST( strncmp( wordData.word, "hello", MAX_WORD_SIZE ) == 0 );
  TEST( wordData.counts[20] == 0 );
  TEST( wordData.hashValue == 471341285 );

}

int main( void ) {

  fprintf( stderr, "Running tests for createWordData...\n" );
  testcreateWordData();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
