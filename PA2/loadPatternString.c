/*
 * Filename: loadPatternString.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa2.h"
#include "pa2Strings.h"

#define DIVIDED_BY_TWO 2

/*
 * Function Name: loadPatternString()
 * Function Prototype: void loadPatternString( unsigned int pattern[],
 *                                             const char * patternStr );
 * Description: Goes through each character in patternStr and, depending on its
 *              value, sets the bits in pattern to either be on or off. The
 *              patternStr is assumed to be exactly 64 characters long, where
 *              each '@' (DEFAULT_ON_CHAR) character represents an "on" bit and
 *              each '-' (DEFAULT_OFF_CHAR) character represents an "off" bit
 * Parameters: pattern[] - array being filled with bits of characters in
 *                         patternStr
 *             patternStr - 64 character string
 * Side Effects: None 
 * Error Conditions: None
 * Return Value: None
 */
void loadPatternString( unsigned int pattern[], const char * patternStr ) {

  // Loop through first 32 bits in patternStr
  for( int i = 0; i < strlen( patternStr ) / DIVIDED_BY_TWO; i++ ) {

    // If the bit in patternStr at index i is the off char '-', shift the bit
    //   pattern in pattern[0] to the left by one bit
    if( patternStr[i] == DEFAULT_OFF_CHAR ) {
      pattern[0] = ( pattern[0]<<1 );
    }

    // If the bit in patternStr at index i is the on char '@', shift the bit
    //   pattern in pattern[0] to the left by one bit and set the last bit to 1
    if( patternStr[i] == DEFAULT_ON_CHAR ) {
      pattern[0] = ( pattern[0]<<1 );
      pattern[0]++;
    }

  }

  // Loop through next 32 bits in patternStr
  for( int i = strlen( patternStr ) / DIVIDED_BY_TWO;
       i < strlen( patternStr ); i++ ) {

    // If the bit in patternStr at index i is the off char '-', shift the bit
    //   pattern in pattern[1] to the left by one bit
    if( patternStr[i] == DEFAULT_OFF_CHAR ) {
      pattern[1] = ( pattern[1]<<1 );
    }

    // If the bit in patternStr at index i is the on char '@', shift the bit
    //   pattern in pattern[1] to the left by one bit and set last bit to 1
    if( patternStr[i] == DEFAULT_ON_CHAR ) {
      pattern[1] = ( pattern[1]<<1 );
      pattern[1]++;
    }

  }

}
