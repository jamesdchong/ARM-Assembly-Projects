/*
 * Filename: drawCoolS.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/18/2019
 * Sources of Help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa1.h"

#define NUMBER_OF_SECTIONS 2

/*
 * Function name: drawCoolS()
 * Function Prototype: void drawCoolS( int size, char fillChar );
 * Description: Prints out entire Cool S design using the given size and
 *              fillChar specified by the user
 * Parameters: size - maximum width of the Cool S
 *             fillChar - the character used to fill in the Cool S design
 * Side Effects: Prints entire Cool S design to stdout
 * Error Conditions: None
 * Return Value: None
 */
void drawCoolS( int size, char fillChar ) {

  // Draws top cap
  drawCap( size, fillChar, 0 );

  // Draws the first straight section
  for( int i = 0; i < size / HALF_DIVISOR - 1; i++ ) {

    printf( "%c", PIPE_CHAR );

    for( int i = 0; i < NUMBER_OF_SECTIONS; i++ ) {

      for( int i = 0; i < size / HALF_DIVISOR - 1; i++ ) {
        printf( "%c", fillChar );
      }

      printf( "%c", PIPE_CHAR );

    }
    printf( "%c", NEWLINE_CHAR );

  }

  // Draws the criss-cross section
  drawCrissCross( size, fillChar );

  // Draws the second straight section
  for( int i = 0; i < size / HALF_DIVISOR - 1; i++ ) {

    printf( "%c", PIPE_CHAR );

    for( int i = 0; i < NUMBER_OF_SECTIONS; i++ ) {

      for( int i = 0; i < size / HALF_DIVISOR - 1; i++ ) {
        printf( "%c", fillChar );
      }

      printf( "%c", PIPE_CHAR );

    }
    printf( "%c", NEWLINE_CHAR );

  }

  // Draws bottom cap
  drawCap( size, fillChar, 1 ); 

}
