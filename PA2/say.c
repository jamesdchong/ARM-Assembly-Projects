/*
 * Filename: say.c
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
 * Function Name: say()
 * Function Prototype: void say( const char * str, char on, char off );
 * Description: Prints out each character in str. For each character is str,
 *              first look up its bit pattern in the appropriate lookup table.
 *              If it is not a valid character, print out error message to
 *              stdout and move on to the next character in str. Otherwise,
 *              print out the character pattern using the specified on and off
 *              bits.
 * Parameters: str - string that will be printed
 *             on - character printed when on
 *             off - character printed when off
 * Side Effects: Prints each character in str to stdout. If its bit pattern is
 *               not a valid character, print error message to stdout.
 * Error Conditions: A character in str is not found in the lookup table. In
 *                   this case, print the corresponding error message to stdout
 * Return Value: None
 */
void say( const char * str, char on, char off ) {

  unsigned int pattern[PATTERN_LEN] = { 0 };
  const char * letters[] = ALPHABET_PATTERNS;
  const char * digits[] = DIGIT_PATTERNS;

  for( int i = 0; i < strlen( str ); i++ ) {

    if( character( pattern, str[i], letters, digits ) == 0 ) {

      printPattern( pattern, on, off );

    } else {

      printf( "%s", STR_ERR_SAY_INVALID_CHAR ) ;

    }

  }

}
