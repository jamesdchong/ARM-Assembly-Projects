/*
 * Filename: lineShouldBePrinted.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function Name: lineShouldBePrinted()
 * Function Prototype: int lineShouldBePrinted( const char * line
 *                                              const argInfo_t * info );
 * Description: Checks if line should be printed in search()
 * Parameters: line - line to be printed if matches regex pattern in info
 *             info - info struct containing regex pattern and bit pattern
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 1 if line should be printed, else 0
 */
int lineShouldBePrinted( const char * line, const argInfo_t * info ) {

  // If line matches the regex pattern
  if( lineMatchesRegex( &info->pattern, line ) == 1 ) {

    // Line should be printed if -v flag is not set
    if( !( ( info->flags & ARG_V_FLAG ) == ARG_V_FLAG ) ) {
      return 1;
    }

    // If line does not match regex pattern
  } else {

      // Line should be printed if -v flag is set
      if( ( info->flags & ARG_V_FLAG ) == ARG_V_FLAG ) {
        return 1;
      }

  }

  // Otherwise, line should not be printed
  return 0;

}
