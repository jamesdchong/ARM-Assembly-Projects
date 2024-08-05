/*
 * Filename: readLine.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

#define NULL_TERMINATOR '\0'
#define EMPTY_STRING ""

/*
 * Function Name: readLine()
 * Function Prototype: char * readLine( FILE * inputFile );
 * Description: Reads a single line from inputFile, stopping at a newline or
 *              when it hits the end-of-file(EOF).
 * Parameters: inputFile - file being passed in
 * Side Effects: Prints error message to stderr if memory allocation fails,
 *               calloc's string on heap and realloc's it when expanding it
 * Error Conditions: - Reached EOF while string is empty -- free string, return
 *                     NULL
 *                   - Memory allocation fails -- print STR_ERR_MEM_EXCEEDED to
 *                     stderr, free string, return NULL
 * Return Value: NULL if any error occurred, else a pointer to the
 *               null-terminated string containing a line from the file
 */
char * readLine( FILE * inputFile ) {

  // Create buf on stack
  char buf[LINE_BUFFER_SIZE];

  // Allocate string on heap
  char * string = calloc( 1, sizeof( char ) );

  // Keeps track of whether or not the file hits a newline
  int hitNewLine = 0;

  // Pointer checking if realloc fails
  char * returnPtr;

  // Loop until line hits newline
  while( 1 ) {

    // If encounter EOF
    if( fgets( buf, LINE_BUFFER_SIZE, inputFile ) == NULL ) {

      // If string empty, free string, return NULL
      if( strcmp( string, EMPTY_STRING ) == 0 ) {
        free( string );
        return NULL;
      }
      return string;

    }

    // Search buf for newline char
    char * ptr = strchr( buf, NEWLINE_CHAR );

    // Replace newline char with null terminator and realloc string
    if( ptr != NULL ) {
      *ptr = NULL_TERMINATOR;

      // Attempt to reallocate string on heap with null terminator
      returnPtr = (char * )realloc( string, strlen(string) + strlen(buf) + 1);
      hitNewLine = 1;
    }
    else {
      // If new line not encountered, Attempt to reallocate string on heap
      //  without null terminator
      returnPtr = (char * )realloc( string, strlen(string) + strlen(buf) );
    }

    // If reallocation fails, print error message, return null
    if( returnPtr == NULL ) {
      fprintf( stderr, STR_ERR_MEM_EXCEEDED );
      free( string );
      return NULL;
    }

    // Set returnPtr to string
    string = returnPtr;

    // Concatenate string with buf
    strncat( string, buf, strlen(buf) );

    // If new line appers, exit loop
    if( hitNewLine == 1 ) {
      break;
    }

    // Reset hitNewLine for next iteration of loop
    hitNewLine = 0;

  }

  // Return string
  return string;
  
}
