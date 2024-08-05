/*
 * Filename: buildWordTable.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include "pa3.h"
#include "pa3Strings.h"

#define NUM_LETTERS 26
#define NULL_TERMINATOR '\0'
#define READ_ONLY "r"

/*
 * Function Name: buildWordTable()
 * Function Prototype: int buildWordTable( wordTable_t * table,
 *                                         unsigned int size );
 * Description: This function will build the table by reading in data from files
 *              of a particular size inside directory DEFAULT_DATA_DIR.
 * Parameters: table - wordTable_t containing slotPtr to element in tableSlot_t
 *                     array and numSlots
 *             size - size of files in DEFAULT_DATA_DIR directory
 * Side Effects: If any error occurs, print message to stderr.
 * Error Conditions:
 *     - Error when opening a file
 *     - Error when tokenizing a line into the word, decade, and count
 *     - Error when parsing the decade and count into numbers
 *     - Error when adding the word into table
 * Return Value: -1 when any addWordCount() call failed, 0 otherwise
 */
int buildWordTable( wordTable_t * table, unsigned int size ) {

  // Create array for path of file
  char buf[BUFSIZ];

  // Initialize letter to 'a'
  char letter = FIRST_LETTER;

  // Loops through each of the letters
  for( int i = 0; i < NUM_LETTERS; i++ ) {

    // Builds path of files being read
    snprintf( buf, BUFSIZ, STR_PATH_JOIN,
              DEFAULT_DATA_DIR, letter, size );

    // Sets errno to 0
    errno = 0;

    // Attempts to open file
    FILE * currFile = fopen( buf, READ_ONLY );

    // If error occurs, print error message and continue to next file
    if( errno != 0 ) {
      fprintf( stderr, STR_ERR_OPENING_FILE , buf, strerror( errno ) );
      continue;
    }

    // Initialize lineNumber to 0
    int lineNumber = 0;

    // Create array for each line
    char line[BUFSIZ];

    // Reads every line of file
    while( fgets( line, BUFSIZ, currFile ) != NULL ) {
      // Increments line number each iteration
      lineNumber++;

      // Makes sure each line is null terminated
      char * ptr = strchr( line, NEWLINE_CHAR );
      if( ptr != NULL ) {
        * ptr = NULL_TERMINATOR;
      }
      
      // Parses word, decade, count
      char * first = strtok( line, DELIMS );
      char * second = strtok( NULL, DELIMS );
      char * third = strtok( NULL, DELIMS );

      // If string cannot be tokenized, print error message, and continue to
      //   next file
      if( first == NULL || second == NULL || third == NULL ) {
        fprintf( stderr, STR_ERR_PARSING_LINE, lineNumber, buf, line );
        continue;
      }

      // Declare endPtr
      char * endPtr;

      // Sets errno to 0
      errno = 0;

      // Attempts to convert decade to unsigned int
      unsigned int decade = strtoul( second, &endPtr, DECADE_BASE );

      // If error occured, print error message and continue to next file
      if( errno != 0 ) {
        fprintf( stderr, STR_ERR_PARSING_LINE, lineNumber, buf, line );
        continue;
      }

      // Sets errno to 0
      errno = 0;

      // Sets longMax to maximum length of long
      unsigned long longMax = ULONG_MAX;

      // Attempts to convert count to unsigned int
      unsigned int count = strtoul( third, &endPtr, COUNT_BASE );

      // If errno is maximum length of long, resent errno to 0
      if( count == longMax ) {
        errno = 0;
      }

      // If error occured, print error message and continue to next file
      if( errno != 0 ) {
        fprintf( stderr, STR_ERR_PARSING_LINE, lineNumber, buf, line );
        continue;
      }

      // Determine index in table word hashes to
      unsigned int index = findSlotIndex( first, table->numSlots );

      // If adding word not successful, close file, return -1
      if( addWordCount( &table->slotPtr[index],
                        first, decade, count ) == -1) {
        fclose( currFile );
        return -1;
      }

    }

    // Close file
    fclose( currFile );

    // Increment letter for next file
    letter++;

  }

  return 0;

}
