/*
 * Filename: pa1.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/19/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "pa1.h"
#include "pa1Strings.h"

#define NEWLINE "\n"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Driver for PA1, checks input by parsing command-line arguments
 *              and checking for errors. If all inputs are valid, it will call
 *              drawCoolS(). Otherwise, it will print the corresponding error
 *              message and return right away.
 * Parameters: argc - number of command line arguments
 *             argv - array holding the command line arguments
 * Side Effects: Prints Cool S to stdout 
 * Error Conditions:
 *   - Incorrect number of command line arguments
 *   - Error converting size to int
 *   - Size contains non-numerical characters
 *   - Size is not in bounds
 *   - Size is not in the format of 4n + 3
 *   - fillChar is not a single character
 *   - fillChar not in bounds
 * Return Value: EXIT_FAILURE if error occurs, EXIT_SUCCESS if no error occurs
 */
int main( int argc, char * argv[] ) {

  if( argc != ARG_NUM ) {

    fprintf( stderr, COOL_S_USAGE, argv[PROG_NAME_IDX], MIN_SIZE, MAX_SIZE,
             MIN_CHAR, MAX_CHAR );
    return EXIT_FAILURE;

  }

  char* endptr;
  char errStr[BUFSIZ];

  // Parse the first number
  errno = 0;
  int size = strtol( argv[SIZE_IDX], &endptr, BASE );

  // Checks for errors converting to int
  if( errno != 0 ) {

    snprintf( errStr, BUFSIZ, SIZE_CONVERT_ERR, argv[SIZE_IDX], BASE );
    perror( errStr );
    fprintf( stderr, NEWLINE );
    return EXIT_FAILURE;

  }

  // Checks for a non-numerical size
  if( *endptr != '\0' ) {

    fprintf( stderr, SIZE_NOT_INT_ERR, BASE );
    return EXIT_FAILURE;

  }

  // Checks if size is in bounds
  if( size < MIN_SIZE || size > MAX_SIZE ) {
    
    fprintf( stderr, SIZE_RANGE_ERR, MIN_SIZE, MAX_SIZE );
    return EXIT_FAILURE;

  }

  // Checks if size if divisible by 4n + 3
  if( ( size - SIZE_OFFSET ) % SIZE_MULTIPLE != 0 ) {

    fprintf( stderr, SIZE_FORMAT_ERR );
    return EXIT_FAILURE;

  }

  // Extract character arg as character array
  char* charArray = argv[CHAR_IDX];

  // Checks if fillChar is a single character
  if( strlen( charArray ) != 1 ) {
  
    fprintf( stderr, SINGLE_CHAR_ERR );
    return EXIT_FAILURE;

  }

  // Take first character of charArray
  char fillChar = charArray[0];
  
  // Checks if fillChar is in bounds
  if( fillChar < MIN_CHAR || fillChar > MAX_CHAR ) {

    fprintf( stderr, CHAR_RANGE_ERR, MIN_CHAR, MAX_CHAR );
    return EXIT_FAILURE;

  }

  // If no errors, print Cool S
  drawCoolS( size, fillChar );

  return EXIT_SUCCESS;

}
