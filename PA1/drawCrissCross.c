/*
 * Filename: drawCrissCross.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of Help: None
 */

#include "pa1.h"

/*
 * Function name: drawCrissCross()
 * Function Prototype: void drawCrissCross( int size, char fillChar );
 * Description: Draws criss-cross portion of the Cool S
 * Parameters: size - maximum width of the Cool S
 *             fillChar - the character used to fill in the Cool S design
 * Side Effects: Prints out the criss-cross design to stdout
 * Error Conditions: None
 * Return Value: None
 */
void drawCrissCross( int size, char fillChar ) {
  
  // Calculate thickness of the Cool S
  int thickness = size / HALF_DIVISOR - 1;

  // Print top portion of criss-cross pattern
  for (int i = 0; i < thickness / HALF_DIVISOR + 1; i++) {
    // Initial whitespace to indent the pattern
    outputCharNTimes(SPACE_CHAR, i);

    // Draw the middle portion of the Cool S shape
    outputChar(BACK_SLASH_CHAR);
    outputCharNTimes(fillChar, thickness);
    outputChar(BACK_SLASH_CHAR);

    // Draw the top portion of the Cool S shape that intersects with the middle
    outputCharNTimes(fillChar, thickness - (DOUBLE * i));
    outputChar(FORWARD_SLASH_CHAR);

    // Output trailing whitespace
    outputCharNTimes(SPACE_CHAR, i);
    outputChar(NEWLINE_CHAR);
  }

  // Print bottom portion of criss-cross pattern
  for (int i = thickness / HALF_DIVISOR; i >= 0; i--) {
    // Initial whitespace to indent the pattern
    outputCharNTimes(SPACE_CHAR, i);

    // Draw the remaining middle portion of the Cool S shape
    outputChar(FORWARD_SLASH_CHAR);
    outputCharNTimes(fillChar, thickness - (DOUBLE * i));
    outputChar(BACK_SLASH_CHAR);

    // Draw the bottom portion of Cool S shape that intersects with the middle
    outputCharNTimes(fillChar, thickness);
    outputChar(BACK_SLASH_CHAR);

    // Output trailing whitespace
    outputCharNTimes(SPACE_CHAR, i);
    outputChar(NEWLINE_CHAR);
  }
}

