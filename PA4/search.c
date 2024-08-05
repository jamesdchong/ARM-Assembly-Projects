/*
 * Filename: search.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 6/3/19
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: search()
 * Function Prototype: int search( const argInfo_t * info,
 *                                 const char * filename );
 * Description: Opens filename and prints all lines that match the regex pattern
 *              found in info.
 * Parameters: info - info struct containing regex pattern and bit pattern
 *             filename - string of file name to be searched
 * Side Effects: All output goes to stdout
 * Error Conditions: - The file could not be opened -- return -1
 * Return Value: -1 if the file could not be opened, else 0
 */
int search( const argInfo_t * info, const char * filename ) {

  // Line returned from readLine()
  char * line;

  // Keeps track of line number in file
  int lineNumber = 0;

  // Open the file
  FILE * currFile = openFile( filename );

  // If file opening fails, return -1
  if( currFile == NULL ) {
    return -1;
  }

  // Loop through file line-by-line
  while( ( line = readLine( currFile ) ) != NULL ) {

    // Increments line number each iteration
    lineNumber++;

    // Check if line should be printed
    if( lineShouldBePrinted( line, info ) == 1 ) {
    
      // If multiple files, print filename
      if( ( info->flags & ARG_MULTI_FILE ) == ARG_MULTI_FILE ) {
        fprintf( stdout, STR_FILENAME, filename );
      }
      
      // If -n flag set, print line number
      if( ( info->flags & ARG_N_FLAG ) == ARG_N_FLAG ) {
        fprintf( stdout, STR_LINENUM, lineNumber );
      }

      // Print line itself
      fprintf( stdout, STR_LINE, line );

    }

    // Free line returned from readLine()
    free( line );

  }

  // Close file after reaching end
  fclose( currFile );
  
  return 0;

}
