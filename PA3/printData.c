/*
 * Filename: printData.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"

#define EMPTY_STRING ""

/*
 * Function Name: printData()
 * Function Prototype: void printData( const wordData_t * word );
 * Description: This function prints out the word statistics in a tabular format
 *              for the given wordData_t to stdout
 * Parameters: word - wordData_t that contains information on what will be
 *                    printed in the function
 * Side Effects: Prints word statistics to stdout
 * Error Conditions: None
 * Return Value: None
 */
void printData( const wordData_t * word ) {

  // Initialize count, decade for looping
  unsigned int count = 0;
  unsigned int decade = MIN_DECADE;

  // Initialize highestCountDecade to save highest count for a word
  unsigned int highestCountDecade = MIN_DECADE;

  // Initialize isEqual if two decades tie for highest count
  int isEqual = 0;

  // Print header
  printf( STR_STATS_HEADER );

  // Loop for each decade in counts array
  for( int i = 0; i < NUM_OF_DECADES; i++ ) {

    // Print decade and count within that decade
    printf( STR_STATS_FMT_COUNT, decade, word->counts[i] );

    // If the count is the highest so far, keep track of it
    if( word->counts[i] >= count ) {

      // If there is a higher count, isEqual is 0
      isEqual = 0;

      // If count is equal to highest count, keep track of it
      if( word->counts[i] == count ) {

        isEqual = 1;

      }

      // Set new highest count to current value of count
      count = word->counts[i];

      // Set current decade to highestCounteDecade
      highestCountDecade = decade;

    }

    // Increment decade by 10
    decade += YEARS_IN_DECADE;

  }

  // If 2 instances of highest count exist, print string including "recently"
  if( isEqual == 1 ) {

    printf( STR_HIGH_COUNT, word->word, STR_MOST_RECENT,
            highestCountDecade, count );

  // Else, print normal highest count string
  } else {

    printf( STR_HIGH_COUNT, word->word, EMPTY_STRING,
            highestCountDecade, count );

  }

}
