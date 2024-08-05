/*
 * Filename: count.c
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
 * Function Name: count()
 * Function Prototype: int count( const argInfo_t * info,
 *                                 const char * filename );
 * Description: Counts number of lines in filename that match pattern found in
 *              info
 * Parameters: info - info struct containing regex pattern and bit pattern
 *             filename - string of file name to be searched
 * Side Effects: All output goes to stdout
 * Error Conditions: - The file could not be opened -- return -1
 * Return Value: -1 if the file could not be opened, else 0
 */
int count( const argInfo_t * info, const char * filename ) {

  // Line returned from readLine()
  char * line;

  // Keeps track of number of lines that match regex pattern
  int count = 0;

  // Open the file
  FILE * currFile = openFile( filename );

  // If file opening fails, return -1
  if( currFile == NULL ) {
    return -1;
  }

  // Read file line-by-line
  while( ( line = readLine( currFile ) ) != NULL ) {

    // Check if line matches the regex pattern in info
    if( lineMatchesRegex( &info->pattern, line ) == 1 
        && ( info->flags & ARG_V_FLAG ) != ARG_V_FLAG ) {

      // Increment count whenever line matches regex pattern and -v flag not set
      count++;

    } else if( lineMatchesRegex( &info->pattern, line ) != 1
               && ( info->flags & ARG_V_FLAG ) == ARG_V_FLAG ) {

      // Increment count when line does not match regex pattern and the -v flag
      //   is set
      count++;

    }

    // Free line returned from readLine()
    free( line );

  }
      
  // If multiple files, print filename
  if( ( info->flags & ARG_MULTI_FILE ) == ARG_MULTI_FILE ) {
    fprintf( stdout, STR_FILENAME, filename );
  }

  // Print count
  fprintf( stdout, STR_COUNT, count );

  // Close file after reaching end
  fclose( currFile );

  return 0;

}
