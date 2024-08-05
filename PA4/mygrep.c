/*
 * Filename: mygrep.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 6/3/19
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Main driver of the program that parses flags and arguments that
 *              are passed in, and runs the functionality of the grep command
 * Parameters: argc - number of command line arguments
 *             argv - array containing command line arguments
 * Side Effects: Error messages printed to stderr, program output to stdout
 * Error Conditions: - The arguments could not be processed -- print error
 *                     message to stderr, return EXIT_FAILURE
 *                   - Regular expression could not be parsed -- print error
 *                     message to stderr, return EXIT_FAILURE
 * Return Value: EXIT_FAILURE on error, else EXIT_SUCCESS
 */
int main( int argc, char * argv[] ) {

  // Create argInfo_t var on stack
  argInfo_t info;

  // Process command line arguments with processArgs()
  int parsing = processArgs( &info, argc, argv );

  // If an error parsing occurs, print error message, return EXIT_FAILURE
  if( parsing == ARG_PARSING_ERROR ) {
    fprintf( stderr, STR_SHORT_USAGE, argv[0], argv[0] );
    return EXIT_FAILURE;
  }

  // If bad regex pattern given, print error message, return EXIT_FAILURE
  if( parsing == REGEX_ERROR ) { 
    fprintf( stderr, STR_ERR_REGEX );
    return EXIT_FAILURE;
  }

  // If --help flag set, print usage message, return EXIT_SUCCESS
  if( ( info.flags & ARG_HELP_FLAG ) == ARG_HELP_FLAG ) {
    fprintf( stdout, STR_USAGE, argv[0], argv[0] );
    return EXIT_SUCCESS;
  }

  // Executes if no file provided as args
  if( optind == argc ) {
  
    // If -c flag set, call count()
    if( ( info.flags & ARG_C_FLAG ) == ARG_C_FLAG ) {
      count( &info, STR_STDIN );

      // If -c flag not set, call search()
    } else {
        search( &info, STR_STDIN );
    }
  
  }

  // Loop through provided files in command line args
  while( optind < argc ) {

    // If -c flag set, call count()
    if( ( info.flags & ARG_C_FLAG ) == ARG_C_FLAG ) {
      count( &info, argv[optind] );

      // If -c flag not set, call search()
    } else {
        search( &info, argv[optind] );
    }

    // Increment to next file in command line args
    optind++;

  }

  // Free regex pattern in info struct
  regfree( &info.pattern );

  return EXIT_SUCCESS;

}
