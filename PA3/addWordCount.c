/*
 * Filename: addWordCount.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/11/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: addWordCount()
 * Function Prototype: int addWordCount( tableSlot_t * slot,
 *                                        const char * word, unsigned int decade
 *                                        unsigned int count );
 * Description: Adds the count for the word and the decade to the tableSlot
 * Parameters: slot - struct in tableSlot_t array containing a wordDataPtr
 *                    pointing to a wordData struct and a numWord field
 *             word - string in wordData
 *             decade - decade string appears
 *             count - number of times string appears in a decade
 * Side Effects: If realloc fails, print error message to stderr.
 * Error Conditions: If realloc fails, print STR_ERR_MEM_EXCEEDED to stderr,
 *                   free the slot's wordDataPtr, and return -1.
 * Return Value: -1 if any error occurred, 0 otherwise
 */
int addWordCount( tableSlot_t * slot, const char * word,
                  unsigned int decade, unsigned int count ) {

  // Calculate index of decade in counts array
  int decadeIdx = ( decade - MIN_DECADE ) / YEARS_IN_DECADE;

  // Make a wordData_t on the stack
  wordData_t wordData;

  // Populate this wordData_t with word, decade, count
  createWordData( &wordData, word, decade, count );

  // Search array of wordData structs to see if same word already exists
  wordData_t * found = bsearch( &wordData, slot->wordDataPtr,
                                slot->numWords, sizeof( struct wordData ),
                                compareWordData );

  // Executes when bsearch finds a wordData_t slot for word
  if( found != NULL ) {
    
    // Increment the count for the decade specified
    found->counts[decadeIdx] += count;

    return 0;

  }

  // Executes if bsearch does not find a wordData_t slot for word
  if( found == NULL ) {

    // Re-allocates array of wordData structs to add new wordData
    wordData_t * returnPtr = realloc( slot->wordDataPtr,
                                      ( slot->numWords + 1 ) *
                                      sizeof( struct wordData ) );

    // Executes if reallocation is not successful
    if( returnPtr == NULL ) {

      // Print error message to stderr
      fprintf( stderr, STR_ERR_MEM_EXCEEDED );

      // Free dynamically allocated memory
      free( slot->wordDataPtr = NULL );

      // Zero out slot's wordDataPtr
      slot->wordDataPtr = NULL;

      return -1;

      // Executes when reallocation is successful
    } else {

        // Set wordDataPtr to the newly allocated array of wordData structs
        slot->wordDataPtr = returnPtr;

        // Insert the created wordData to the end of the array
        slot->wordDataPtr[slot->numWords] = wordData;

        // Increment the number of unique words in the arrray
        slot->numWords += 1;

        // Sort the array based on compareWordData
        qsort( slot->wordDataPtr, slot->numWords, sizeof( struct wordData ),
               compareWordData);

    }

  }

  return 0;

}
