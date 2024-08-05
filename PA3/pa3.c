/*
 * Filename: pa3.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#include "pa3.h"
#include "pa3Strings.h"

#define FILE_SIZE_ZERO 0
#define FILE_SIZE_ONE 1
#define FILE_SIZE_TWO 2
#define FILE_SIZE_THREE 3
#define FILE_SIZE_FOUR 4
#define FILE_SIZE_FIVE 5

#define UNKNOWN_FLAGS '?'

#define NULL_TERMINATOR '\0'

/*
 * Function Name: main()
 * Function Prototype: int main ( int argc, char * argv[] );
 * Description: Main driver of the program. Its main tasks are to parse any
 *              command line arguments that are passed in and start the
 *              user-interactive mode. By default, the number of slots in the
 *              table will be 11 and the data file size will be 50.
 * Parameters: argc - number of command line arguments
 *             argv - array holding the command line arguments
 * Side Effects: If any reason for error occurs, print error message to stderr.
 * Error Conditions:
 *     - Invalid flags passed in ( getopt() will print error message )
 *     - Argument passed in is invalid due to incorrect format or invalid input
 *       (not in range or not valid file size)
 *     - Memory allocation issues due to *alloc() functions
 *     - Failed to buildWordTable()
 * Return Value: EXIT_FAILURE if any error occurs, EXIT_SUCCESS if program exit
 *               due to user exiting from the interactive loop
 */
int main( int argc, char * argv[] ) {

  int c;

  // Initialize default numSlots to be 11, default fileSize to be 50
  unsigned int numSlots = DEFAULT_NUM_SLOTS;
  unsigned int fileSize = DEFAULT_FILE_SIZE;

  // Temporary numSlots and fileSize string holders for command line arguments
  //   not yet parsed
  char * tempNumSlots;
  char * tempFileSize;

  // Keeps track of which flags were entered by user
  int nFlag = 0;
  int sFlag = 0;

  // Parse flags using getopt
  while( ( c = getopt( argc, argv, OPTSTRING ) ) != -1 ) {

    switch( c ) {

      // Case for help (-h) flag
      case HELP_FLAG:
      fprintf( stdout, STR_USAGE, argv[0], DEFAULT_DATA_DIR, MIN_NUM_SLOTS,
                 MAX_NUM_SLOTS, DEFAULT_NUM_SLOTS, DEFAULT_FILE_SIZE );
        return EXIT_SUCCESS;

      // Case to provide name (-n)
      case NUM_SLOTS_FLAG:
        tempNumSlots = optarg;
        nFlag = 1;
        break;

      // Case to provide size (-s)
      case FILE_SIZE_FLAG:
        tempFileSize = optarg;
        sFlag = 1;
        break;

      // Case to catch all unknown flags, getopt() automatically prints error
      //   message
      case UNKNOWN_FLAGS:
      default:
        return EXIT_FAILURE;

    }

  }

  // Check for extra arguments after getopt completes
  if( optind < argc ) {
    fprintf( stderr, STR_ERR_EXTRA_ARG, argv[optind] );
    return EXIT_FAILURE;
  }

  // Executes if numSlots is not the default value
  if( nFlag == 1 ) {

    // Declares endPtr
    char * endPtr;

    // Set errno to 0
    errno = 0;

    // Attempt to convert to unsigned int
    numSlots = strtoul( tempNumSlots, &endPtr, NUM_SLOTS_BASE );

    // If error occured, print error message and return EXIT_FAILURE
    if( errno != 0  ) {
      fprintf( stderr, STR_ERR_CONVERTING,
               STR_NUM_SLOTS_ARGNAME, tempNumSlots,
               NUM_SLOTS_BASE, strerror( errno ) );
      return EXIT_FAILURE;
    }

    // If invalid character in string, print error message, return EXIT_FAILURE
    if( *endPtr != NULL_TERMINATOR ) {
      fprintf( stderr, STR_ERR_NOT_INT, STR_NUM_SLOTS_ARGNAME,
               tempNumSlots, NUM_SLOTS_BASE );
      return EXIT_FAILURE;
    }
  
    // If numSlots not within [3, 421], print error message, return EXIT_FAILURE
    if( intervalContains( MIN_NUM_SLOTS, MAX_NUM_SLOTS, numSlots ) != 1 ) {
      fprintf( stderr, STR_ERR_NUM_SLOTS_INTERVAL, numSlots,
               MIN_NUM_SLOTS, MAX_NUM_SLOTS );
      return EXIT_FAILURE;
    }

  }

  // Executes if fileSize is not the default value
  if( sFlag == 1 ) {

    // Declare endPtr
    char * endPtr;

    // Set errno to 0
    errno = 0;

    // Attempt to convert to unsigned int
    fileSize = strtoul( tempFileSize, &endPtr, SIZE_BASE );

    // If error occured, print error message, return EXIT_FAILURE
    if( errno != 0 ) {
      fprintf( stderr, STR_ERR_CONVERTING,
               STR_SIZE_ARGNAME, tempFileSize, SIZE_BASE, strerror( errno ) );
      return EXIT_FAILURE;
    }

    // If invalid character in string, print error message, return EXIT_FAILURE
    if( *endPtr != NULL_TERMINATOR ) {
      fprintf( stderr, STR_ERR_NOT_INT, STR_SIZE_ARGNAME,
               tempFileSize, SIZE_BASE );
      return EXIT_FAILURE;
    }
 
    // Initialize allowedFileSizes array to array containing 1, 5, 10, 50, 100,
    //   500
    int allowedFileSizes[] = ALLOWED_FILE_SIZES;

    // If fileSize not within array, print error message, return EXIT_FAILURE
    if( fileSize != allowedFileSizes[FILE_SIZE_ZERO] &&
        fileSize != allowedFileSizes[FILE_SIZE_ONE] &&
        fileSize != allowedFileSizes[FILE_SIZE_TWO] &&
        fileSize != allowedFileSizes[FILE_SIZE_THREE] &&
        fileSize != allowedFileSizes[FILE_SIZE_FOUR] &&
        fileSize != allowedFileSizes[FILE_SIZE_FIVE] ) {

      fprintf( stderr, STR_ERR_SIZE_INVALID, fileSize );
      return EXIT_FAILURE;

    }

  }

  // Allocate a wordTable_t on stack
  wordTable_t wordTable;

  // Initialize its numSlots member to parsed numSlots value
  wordTable.numSlots = numSlots;

  // Allocate zero-filled array of tableSlot_t into slotPtr
  wordTable.slotPtr = calloc( numSlots, sizeof( struct tableSlot ) );

  // If calloc fails, print error message, return EXIT_FAILURE
  if( wordTable.slotPtr == NULL ) {
    fprintf( stderr, STR_ERR_MEM_EXCEEDED );
    return EXIT_FAILURE;
  }

  // Calls buildWordTable and stores return value in failCheck
  int failCheck = buildWordTable( &wordTable, fileSize );

  // If buildWordTable() fails, free dynamically allocated memory, return
  //   EXIT_FAILURE
  if( failCheck == -1 ) {

    // Free all dynamically allocated memory
    for( int i = 0; i < wordTable.numSlots; i++ ) {
      free( wordTable.slotPtr[i].wordDataPtr );
      wordTable.slotPtr[i].wordDataPtr = NULL;
    }

    free( wordTable.slotPtr );
    wordTable.slotPtr = NULL;

    return EXIT_FAILURE;
  }

  // Call user interactive mode
  interactiveLoop( &wordTable );

  // Free all dynamically allocated memory
  for( int i = 0; i < wordTable.numSlots; i++ ) {
    free( wordTable.slotPtr[i].wordDataPtr );
    wordTable.slotPtr[i].wordDataPtr = NULL;

  }

  free( wordTable.slotPtr );
  wordTable.slotPtr = NULL;

  return EXIT_SUCCESS;

}
