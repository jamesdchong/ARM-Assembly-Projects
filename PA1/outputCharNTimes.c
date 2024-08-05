/*
 * Filename: outputCharNTimes.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

#include <stdio.h>

#include "pa1.h"

/*
 * Function Name: outputCharNTimes()
 * Function Prototype: void outputCharNTimes( char ch, int n );
 * Description: Prints the passed in char n times
 * Parameters: ch - the character to be printed
 *             n - the amount of times the char will be printed
 * Side Effects - None
 * Error Conditions: If n is less than 1, nothing will be printed
 * Return Value: None
 */
void outputCharNTimes( char ch, int n ) {

  // Print ch only if n is greater than 0
  if( n > 0 ) {

    // Print each ch n amount of times
    for( int i = 0; i < n; i++ ) {

      outputChar( ch );

    }

  }

}
