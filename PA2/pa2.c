/*
 * Filename: pa2.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/4/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa2.h"
#include "pa2Strings.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Main driver of the program. Its main tasks are to parse any
 *              command line arguments that are passed in and start the
 *              user-interactive mode. By default, the "on" character and the
 *              "off" character should be '@' and '-', repsectively
 * Parameters: argc - number of command line arguments
 *             argv - array holding the command line arguments
 * Side Effects: If any reason for error occurs, print error message to stderr.
 * Error Conditions: 
 *    - Number of arguments not between 0 and 2
 *    - First argument ("on" character) was not a single character
 *    - First argument ("on" character) not between ' ' and '~'
 *    - Second argument ("off" character) not a single character
 *    - Second argument ("off" character) not between ' ' and '~'
 * Return Value: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main( int argc, char * argv[] ) {

  // Excludes executable name in command line argument count
  argc--;

  // Default on and off chars
  char on = DEFAULT_ON_CHAR;
  char off = DEFAULT_OFF_CHAR;

  // Checks if number of arguments is between 0 and 2
  if( argc < MIN_EXPECTED_ARGS || argc > MAX_EXPECTED_ARGS ) {
    fprintf( stderr, STR_USAGE, argv[0], on, off, MIN_ASCII, MAX_ASCII );
    return EXIT_FAILURE;
  }

  // When no command line arguments are passed in
  if( argc == 0 ) {

    // Calls commandLoop function with default on and off chars
    commandLoop( on, off );

  }

  // When one command line argument is passed in
  if( argc == 1 ) {

    // Checks if on char is one character
    if( strlen( argv[ON_CHAR_IDX] ) != 1 ) {
      fprintf( stderr, STR_ERR_SINGLE_CHAR, ON_ARG_NAME, argv[ON_CHAR_IDX] );
      return EXIT_FAILURE;
    }

    // Checks if on char is within ascii range
    if( (int) * argv[ON_CHAR_IDX] < MIN_ASCII ||
        (int) * argv[ON_CHAR_IDX] > MAX_ASCII ) {

      fprintf( stderr, STR_ERR_CHAR_RANGE, ON_ARG_NAME,
               (int) * argv[ON_CHAR_IDX], MIN_ASCII, MAX_ASCII );
      return EXIT_FAILURE;

    }

    // Sets first command line arg to "on" char
    on = ( *argv[ON_CHAR_IDX] );

    // Calls commandLoop function with on char and default off char
    commandLoop( on, off );

  }

  // When two command line arguments are passed in
  if( argc == MAX_EXPECTED_ARGS ) {

    // Checks if on char is one character
    if( strlen( argv[ON_CHAR_IDX] ) != 1 ) {
      fprintf( stderr, STR_ERR_SINGLE_CHAR, ON_ARG_NAME, argv[ON_CHAR_IDX] );
      return EXIT_FAILURE;
    }

    // Checks if on char is within ascii range
    if( (int) * argv[ON_CHAR_IDX] < MIN_ASCII ||
        (int) * argv[ON_CHAR_IDX] > MAX_ASCII ) {

      fprintf( stderr, STR_ERR_CHAR_RANGE, ON_ARG_NAME,
               (int) * argv[ON_CHAR_IDX], MIN_ASCII, MAX_ASCII );
      return EXIT_FAILURE;

    }

    // Checks if off char is one character
    if( strlen( argv[OFF_CHAR_IDX] ) != 1 ) {
      fprintf( stderr, STR_ERR_SINGLE_CHAR, OFF_ARG_NAME, argv[OFF_CHAR_IDX] );
      return EXIT_FAILURE;
    }

    // Checks if off char is within ascii range
    if( (int) * argv[OFF_CHAR_IDX] < MIN_ASCII ||
        (int) * argv[OFF_CHAR_IDX] > MAX_ASCII ) {

      fprintf( stderr, STR_ERR_CHAR_RANGE, OFF_ARG_NAME,
               (int) * argv[OFF_CHAR_IDX], MIN_ASCII, MAX_ASCII );
      return EXIT_FAILURE;
    }

    // Sets first command line arg to "on" char
    on = ( *argv[ON_CHAR_IDX] );
    
    // Sets second command line arg to "off" char
    off = ( *argv[OFF_CHAR_IDX] );

    // Calls commandLoop function with on and off chars
    commandLoop( on, off );

  }

}

