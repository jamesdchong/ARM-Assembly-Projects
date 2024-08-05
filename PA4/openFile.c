/*
 * Filename: openFile.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 6/3/19
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: openFile()
 * Function Prototype: FILE * openFile( const char * filename );
 * Description: Opens filename so that it can be read.
 * Parameters: filename - string of file name to be opened
 * Side Effects: Prints error messages to stderr.
 * Error Conditions: - We can't stat the file - print error message to stderr,
 *                     return NULL
 *                   - The file is a directory - print error message to stderr,
 *                     return NULL
 *                   - The file could not be opened - print error message to
 *                     stderr, return NULL
 * Return Value: NULL if any error occurred, else a pointer to the opened file
 */
FILE * openFile( const char * filename ) {

  // If filename is "-", return stdin
  if( strcmp( filename, STR_STDIN ) == 0 ) {
    return stdin;
  }

  // Create sbuf on stack
  struct stat sbuf;

  // Set errno to 0
  errno = 0;

  // Call stat to check if filename is a regular file
  stat( filename, &sbuf );

  // If filename not a regular file, print error message, return NULL
  if( errno != 0 ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror( errno ) );
    return NULL;
  }

  // If the file is a directory, print error message, return NULL
  if( S_ISDIR( sbuf.st_mode ) ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror( EISDIR ) );
    return NULL;
  }

  // Reset errno to 0
  errno = 0;

  // Attempt to open filename
  FILE * currFile = fopen( filename, STR_OPEN_READ );

  // If any error opening the file, print error message, return NULL
  if( errno != 0 ) {
    fprintf( stderr, STR_ERR_OPEN_FILE, filename, strerror( errno ) );
    return NULL;
  }

  // Return pointer to opened file
  return currFile;

}
