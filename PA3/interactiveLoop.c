/*
 * Filename: interactiveLoop.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa3.h"
#include "pa3Strings.h"

#define NULL_TERMINATOR '\0'
#define ARBITRARY_DECADE 1800
#define ARBITRARY_COUNT 420

/*
 * Function Name: interactiveLoop()
 * Function Prototype: void interactiveLoop( const wordTable_t * table );
 * Description: This function allows user to interactively search through the
 *              table for a specific word. It first prints out a list of
 *              possible commands. It should only print this usage message if
 *              shouldPrompt() returns 1. The function then prompts the user to
 *              enter a command. This function continues to reprompt the user
 *              until the user enters Ctrl-D (signals EOF).
 * Parameters: table - wordTable_t containing slotPtr to element in tableSlot_t
 *                     array and numSlots
 * Side Effects: Any error messages printed to stdout
 * Error Conditions:
 *     - String could not be tokenized
 *     - Unrecognized command
 *     - Missing arguments
 *     - Extra arguments
 *     - Target wordData_t in table not found
 * Return Value: None
 */
void interactiveLoop( const wordTable_t * table ) {

  // Buffer array
  char buffer[BUFSIZ];

  // Prompts the user to enter command if shouldPrompt() returns 1
  if( shouldPrompt() == 1 ) {
    fprintf( stdout, STR_HELP );
  }

  // Continues to reprompt the user until ctrl-D (EOF char) and reads line of
  //   input
  for( PRINT_PROMPT; fgets( buffer, BUFSIZ, stdin ) != NULL; PRINT_PROMPT ) {

    // Replaces new line char with null terminating char at end of input
    char * ptr = strchr( buffer, NEWLINE_CHAR );
    if( ptr != NULL ) {
      * ptr = NULL_TERMINATOR;
    }

    // Extracts command from input
    char * command = strtok( buffer, DELIMS );

    // If nothing entered, reprompt user
    if( command == NULL ) {
      continue;
    }

    // List of valid commands
    const char * commandList[] = COMMANDS;

    // Extract index of command in commandList
    int commandIndex = findCommand( command, commandList );

    // If command is invalid, print error message and reprompt user
    if( commandIndex == -1 ) {
      fprintf( stdout, STR_ERR_BAD_COMMAND );
      continue;
    }

    // If command is "help", print message and reprompt user
    if( commandIndex == HELP ) {
      fprintf( stdout, STR_HELP );
      continue;
    }

    // If command is "data" or "plot" parse argument that follows
    if( commandIndex == DATA || commandIndex == PLOT ) {

      // Extract word argument
      char * word = strtok( NULL, DELIMS );

      // If word arg missing, print error message, reprompt user
      if( word == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If trailing args, print error message, reprompt user
      char * check = strtok( NULL, DELIMS );
      if( check != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG, check );
        continue;
      }

      // Allocate wordData on stack
      wordData_t wordData;

      // Create temporary wordData_t with word to search for target
      createWordData( &wordData, word, ARBITRARY_DECADE, ARBITRARY_COUNT );

      // Find index of slot that might contain word in the table
      int index = findSlotIndex( word, table->numSlots );

      // Use binary search to get target wordData_t in table
      wordData_t * target = bsearch( &wordData,
                                     table->slotPtr[index].wordDataPtr, 
                                     table->slotPtr[index].numWords,
                                     sizeof( struct wordData ),
                                     compareWordData );

      // If target not found, print error message, reprompt user
      if( target == NULL ) {
        fprintf( stdout, STR_NO_DATA );
        continue;
      }

      // If command is "plot", call buildPlot() and printPlot()
      if( commandIndex == PLOT ) {

        // Declare 2d array
        char plotArr[PLOT_ROWS][PLOT_COLS];

        // Initialize array with all blank space chars
        for( int i = 0; i < PLOT_ROWS; i++ ) {
          for( int j = 0; j < PLOT_COLS; j++ ) {
            plotArr[i][j] = PLOT_SPACE_CHAR;
          }
        }

        // Set initial minCount and maxCount to first element in counts array
        unsigned int minCount = target->counts[0];
        unsigned int maxCount = target->counts[0];

        // Loops through each count in counts array
        for( int i = 0; i < NUM_OF_DECADES; i++ ) {

          // Finds maximum count in counts array
          if( target->counts[i] > maxCount ) {
            maxCount = target->counts[i];
          }

          // Finds minimum count in counts array
          if( target->counts[i] < minCount ) {
            minCount = target->counts[i];
          }

        }

        // Calls buildPlot to fill plotArr
        buildPlot( plotArr, target, minCount, maxCount );

        // Calls printPlot to print plotArr filled in buildPlot()
        printPlot( plotArr, minCount, maxCount );

      }

      // If command is "data", call printData()
      if( commandIndex == DATA ) {

        // Calls printData to print decades and corresponding counts
        printData( target );

      }

    }

  }

  fprintf( stdout, STR_END_PROMPT );

}
