/*
 * Filename: commandLoop.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/4/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "pa2.h"
#include "pa2Strings.h"

#define NEWLINE_CHAR '\n'
#define NULL_TERMINATOR '\0'

/*
 * Function Name: commandLoop()
 * Function Prototype: void commandLoop( char on, char off );
 * Description: Function that allows user to interactively manipulate bits in
 *              the pattern. After user inputs command, call that function and
 *              printPattern(). Afterwards, print prompt and repeat process.
 * Parameters: on - character printed when on
 *             off - character printed when off
 * Side Effects: Prints list of possible commands, prompts the user to enter a
 *               a command, and continues to do so until EOF character, all to
 *               stdout. If at any point an error occurs, print corresponding
 *               error message to stdout.
 * Error Conditions: If any error occurs, print error message to stdout,
 *                   re-prompt user:
 *   - Command unrecognized
 *   - Any missing arguments for set, clear, toggle, character, say,
 *     scrollHorizontal, scrollVertical, translate
 *   - Any trailing, unnecessary arguments for set, clear. toggle, invert,
 *     character, say, scrollHorizontal, scrollVertical, translate
 *   - Error parsing arguments for set, clear, toggle, scrollHorizontal,
 *     scrollVertical, translate
 *   - Arg not a single character for "character" command
 *   - Error setting pattern for "character" command
 *
 * Return Value: None
 */
void commandLoop( char on, char off ) {

  // Buffer array
  char buffer[BUFSIZ];

  // Pattern array
  unsigned int pattern[PATTERN_LEN] = { 0 };

  // Prompts the user to enter command if shouldPrompt() returns 1
  if( shouldPrompt() == 1 ) {
    fprintf( stdout, STR_COMMAND_USAGE );
  }

  // Continues to re-prompt the user until the user enters ctrl-D (EOF char) and
  //   reads line of input
  for( PRINT_PROMPT; fgets( buffer, BUFSIZ, stdin ) != NULL; PRINT_PROMPT ) {

    // Replaces new line char with null terminating char at end of input
    char * ptr = strchr( buffer, NEWLINE_CHAR );
    if( ptr != NULL ) {
      * ptr = NULL_TERMINATOR;
    }

    // Extracts command from input
    char * command = strtok( buffer, DELIM );

    // If nothing entered, re-prompt user
    if( command == NULL ) {
      continue;
    }

    // List of valid commands
    const char * commandList[] = COMMANDS;

    // Extract index of command in commandList
    int commandIndex = findCommand( command, commandList );  

    // If command is invalid, print error message and re-prompt user
    if( commandIndex == -1 ) {
      fprintf( stdout, STR_ERR_BAD_COMMAND );
      continue;
    }

    // If command is "help", print error message and re-prompt user
    if( commandIndex == HELP ) { 
      fprintf( stdout, STR_COMMAND_USAGE );
      continue;
    }
  
    // If command is "set", "clear", or "toggle", check args and print pattern
    if( commandIndex == SET || commandIndex == CLEAR ||
        commandIndex == TOGGLE ) {

      // Extract first and second arguments
      char * arg0 = strtok( NULL, DELIM );
      char * arg1 = strtok( NULL, DELIM );

      // If either argument is missing, print error message and re-prompt user
      if( arg0 == NULL || arg1 == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If extra argument, print error message and re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // Declare endPtr
      char * endPtr;

      // Set errno to 0
      errno = 0;

      // Attempt to convert first arg to unsigned int
      unsigned int part0 = strtoul( arg0, &endPtr, 0 );

      // If error occured, print error message and re-prompt user
      if( errno != 0 || *endPtr != NULL_TERMINATOR ) {
        fprintf( stdout, STR_ERR_PATTERN_INVALID );
        continue;
      }

      // Reset errno to 0
      errno = 0;

      // Attempt to convert second arg to unsigned int
      unsigned int part1 = strtoul( arg1, &endPtr, 0 );

      // If error occured, print error message and re-prompt user
      if( errno != 0 || *endPtr != NULL_TERMINATOR ) {
        fprintf( stdout, STR_ERR_PATTERN_INVALID );
        continue;
      }      
  
      // If command is "set", call its function print pattern, re-prompt
      if( commandIndex == SET ) {
        set( pattern, part0, part1 );
        printPattern( pattern, on, off );
        continue;
      }

      // If command is "clear", call its function, print pattern, re-prompt
      if( commandIndex == CLEAR ) {
        clear( pattern, part0, part1 );
        printPattern( pattern, on, off );
        continue;
      }

      // If command is "toggle", call its function, print pattern, re-prompt
      if( commandIndex == TOGGLE ) {
        toggle( pattern, part0, part1 );
        printPattern( pattern, on, off );
        continue;
      } 

    }

    // If command is "invert", check args and print pattern
    if( commandIndex == INVERT ) {

      // If any extra arguments, print error message and re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // Call invert, print pattern, and re-prompt user
      invert( pattern );
      printPattern( pattern, on, off );
      continue;

    }

    // If command is "character", check args and print pattern
    if( commandIndex == CHARACTER ) {

      // Extract arg after command
      char * arg = strtok( NULL, DELIM );

      // If no arg, print error message, re-prompt user
      if( arg == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If extra arg, print error message, re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // If character is not a single char, print error message, re-prompt
      if( strlen( arg ) != 1 ) {
        fprintf( stdout, STR_ERR_CHAR_COMMAND_SINGLE );
        continue;
      }

      // argChar is the first character of the argument passed in
      char argChar = arg[0];

      const char * alphabet[] = ALPHABET_PATTERNS;
      const char * digits[] = DIGIT_PATTERNS;

      // If argChar is not valid, print error message, re-prompt user, else
      //   print pattern after calling character
      if( character( pattern, argChar, alphabet, digits ) == -1 ) {
        fprintf( stdout, STR_ERR_CHAR_INVALID );
        continue;
      } else {
        printPattern( pattern, on, off );
        continue;
      }

    }

    // If command is "say", check args and print pattern
    if( commandIndex == SAY ) {

      // Extracts argument
      char * arg = strtok( NULL, DELIM );
    
      // If no arg, print error message, re-prompt user
      if( arg == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If extra arg, print error message, re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // Call say with the string passed in as argument, re-prompt user
      say( arg, on, off );
      continue;

    }

    // If command is "scrollHorizontal" or "scrollVertical", check args and call
    //   corresponding function and print pattern
    if( commandIndex == SCROLL_HORIZONTAL || commandIndex == SCROLL_VERTICAL ) {
    
      // Extract argument from input
      char * arg = strtok( NULL, DELIM );

      // If no arg, print error message, re-prompt user
      if( arg == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If extra arg, print error message, re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // Declar endPtr
      char * endPtr;

      // Set errno to 0
      errno = 0;

      // Attempt to convert arg to signed int
      signed int offset = strtol( arg, &endPtr, 0 );

      // If error occured, print error message and re-prompt user
      if( errno != 0 || *endPtr != NULL_TERMINATOR ) {
        fprintf( stdout, STR_ERR_INT_INVALID );
        continue;
      }

      // If command "scrollHorizontal", call function and print pattern
      if( commandIndex == SCROLL_HORIZONTAL ) {
        scrollHorizontal( pattern, offset );
        printPattern( pattern, on, off );
        continue;
      }

      // If command "scrollVertical", call function and print pattern
      if( commandIndex == SCROLL_VERTICAL ) {
        scrollVertical( pattern, offset ) ;
        printPattern( pattern, on, off );
        continue;
      }

    }

    // If command is "translate", check args, call function and re-prompt user
    if( commandIndex == TRANSLATE ) {

      // Extract two args from input
      char * arg0 = strtok( NULL, DELIM );
      char * arg1 = strtok( NULL, DELIM );

      // If missing args, print error message and re-prompt user
      if( arg0 == NULL || arg1 == NULL ) {
        fprintf( stdout, STR_ERR_COMMAND_MISSING_ARG );
        continue;
      }

      // If extra args, print error message and re-prompt user
      if( strtok( NULL, DELIM ) != NULL ) {
        fprintf( stdout, STR_ERR_EXTRA_ARG );
        continue;
      }

      // Declare endPtr
      char * endPtr;

      // Set errno to 0
      errno = 0;

      // Attempt to convert first arg to signed int
      signed int hOffset = strtol( arg0, &endPtr, 0 );

      // If error occured, print error message and re-prompt user
      if( errno != 0 || *endPtr != NULL_TERMINATOR ) {
        fprintf( stdout, STR_ERR_INT_INVALID );
        continue;
      }
      
      // Reset errno to 0
      errno = 0;
  
      // Attempt to convert second arg to signed int
      signed int vOffset = strtol( arg1, &endPtr, 10 );

      // If error occured, print error message and re-prompt user
      if( errno != 0 || *endPtr != NULL_TERMINATOR ) {
        fprintf( stdout, STR_ERR_INT_INVALID );
        continue;
      }

      // Call translate, print pattern, and re-prompt user
      translate( pattern, hOffset, vOffset );
      printPattern( pattern, on, off );
      continue;

    }

  }
  
  // Print newline at end of program
  fprintf( stdout, STR_END_PROMPT );

}
