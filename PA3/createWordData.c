/*
 * Filename: createWordData.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/11/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa3.h"

#define NULL_TERMINATOR '\0'

/*
 * Function Name: createWordData()
 * Function Prototype: void createWordData( wordData_t * wordData,
 *                                          const char * wordStr,
 *                                          unsigned int decade,
 *                                          unsigned int count );
 * Description: Populates the fields of the wordData struct to represent the
 *              word in wordStr.
 * Parameters: wordData - struct with fields word string array, hashValue, count
 *                        integer array
 *             wordStr - string to be placed in wordData
 *             decade - decade string appears
 *             count - number of times string appears in a decade
 * Side Effects: None 
 * Error Conditions: None
 * Return Value: None
 */
void createWordData( wordData_t * wordData, const char * wordStr,
                     unsigned int decade, unsigned int count ) {

  // Calculate index of decade
  int decadeIdx = ( decade - MIN_DECADE ) / YEARS_IN_DECADE;

  // Copy wordStr into wordData's word field
  strncpy( wordData->word, wordStr, MAX_WORD_SIZE );

  // If string's length greater than 48, null terminate the string at index 47
  wordData->word[ MAX_WORD_SIZE - 1 ] = NULL_TERMINATOR;

  // Set all numbers in wordData's counts array to 0
  for( int i = 0; i < sizeof( wordData->counts ) / sizeof( int ); i++ ) {
    wordData->counts[i] = 0;
  }

  // Set item of counts array at index of decade to be count
  wordData->counts[decadeIdx] = count;

  // Set wordData's hash value using computeHash()
  wordData->hashValue = computeHash( wordData->word );

}
