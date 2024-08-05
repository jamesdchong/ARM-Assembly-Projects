/*
 * Filename: scrollHorizontal.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa2.h"
#include "pa2Strings.h"

#define MASK_ONE 0xFF000000
#define MASK_TWO 0x00FF0000
#define MASK_THREE 0x0000FF00
#define MASK_FOUR 0x000000FF

#define KEEP_LAST_BIT 0x00000001
#define KEEP_FIRST_BIT 0x00000080

#define BYTE_SIZE 8
#define SHIFT_THREE_BYTES 3
#define SHIFT_TWO_BYTES 2
#define SHIFT_ONE_BYTE 1

#define SHIFT_RESULT 7

/*
 * Function Name: scrollHorizontal()
 * Function Prototype: void scrollHorizontal( unsigned int pattern[],
 *                                            int offset );
 * Description: Scroll pattern horizontally based on offset. If offset is
 *              positive, scroll right and wrap the bits around to the left. If
 *              offset is negative, scroll left and wrap the bits around to the
 *              right.
 * Parameters: pattern[] - two element array holding tow halves of a patter
 *             offset - number of positions
 * Side Effects: None 
 * Error Conditions: None
 * Return Value: None
 */
void scrollHorizontal( unsigned int pattern[], int offset ) {

  unsigned int mask;
  unsigned int result;

  // Mask to keep last bit
  unsigned int keepLastBit;

  // Mask to keep first bit
  unsigned int keepFirstBit;

  // Vars for first byte
  unsigned int first;
  unsigned int maskedFirst;  
  unsigned int firstShiftedResult;

  // Vars for second byte
  unsigned int second;
  unsigned int maskedSecond;
  unsigned int secondShiftedResult;

  // Vars for third byte
  unsigned int third;
  unsigned int maskedThird;
  unsigned int thirdShiftedResult;

  // Vars for fourth byte
  unsigned int fourth;
  unsigned int maskedFourth;
  unsigned int fourthShiftedResult;
 
  // Run when offset is positive
  if( offset >= 0 ) {

    // Scroll Horizontally for pattern[0]
    for( int i = 0; i < offset; i++ ) {

      // Mask first byte of pattern[0], move last bit to front and shift right
      first = pattern[0];
      mask = MASK_ONE;
      maskedFirst = first & mask;
      maskedFirst = ( maskedFirst >> ( BYTE_SIZE * SHIFT_THREE_BYTES ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedFirst & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedFirst = ( maskedFirst >> 1 );
      firstShiftedResult = ( maskedFirst | result );

      // Mask second byte of pattern[0], move last bit to front and shift right
      second = pattern[0];
      mask = MASK_TWO;
      maskedSecond = second & mask;
      maskedSecond = ( maskedSecond >> ( BYTE_SIZE * SHIFT_TWO_BYTES ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedSecond & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedSecond = ( maskedSecond >> 1 );
      secondShiftedResult = ( maskedSecond | result );

      // Mask third byte of pattern[0], move last bit to front and shift right
      third = pattern[0];
      mask = MASK_THREE;
      maskedThird = third & mask;
      maskedThird = ( maskedThird >> ( BYTE_SIZE * SHIFT_ONE_BYTE ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedThird & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedThird = ( maskedThird >> 1 );
      thirdShiftedResult = ( maskedThird | result );

      // Mask fourth byte of pattern[0], move last bit to front and shift right
      fourth = pattern[0];
      mask = MASK_FOUR;
      maskedFourth = fourth & mask;
      maskedFourth = ( maskedFourth >> 0 );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedFourth & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedFourth = ( maskedFourth >> 1 );
      fourthShiftedResult = ( maskedFourth | result );

      // Add firstShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + firstShiftedResult;

      // Add secondShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + secondShiftedResult;

      // Add thirdShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + thirdShiftedResult;      

      // Add fourthShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + fourthShiftedResult;

    }

    // Scroll horizontally for pattern[1]
    for( int i = 0; i < offset; i++ ) {

      // Mask first byte of pattern[1], move last bit to front and shift right
      first = pattern[1];
      mask = MASK_ONE;
      maskedFirst = first & mask;
      maskedFirst = ( maskedFirst >> ( BYTE_SIZE * SHIFT_THREE_BYTES ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedFirst & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedFirst = ( maskedFirst >> 1 );
      firstShiftedResult = ( maskedFirst | result );

      // Mask second byte of pattern[1], move last bit to front and shift right
      second = pattern[1];
      mask = MASK_TWO;
      maskedSecond = second & mask;
      maskedSecond = ( maskedSecond >> ( BYTE_SIZE * SHIFT_TWO_BYTES ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedSecond & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedSecond = ( maskedSecond >> 1 );
      secondShiftedResult = ( maskedSecond | result );

      // Mask third byte of pattern[1], move last bit to front and shift right
      third = pattern[1];
      mask = MASK_THREE;
      maskedThird = third & mask;
      maskedThird = ( maskedThird >> ( BYTE_SIZE * SHIFT_ONE_BYTE ) );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedThird & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedThird = ( maskedThird >> 1 );
      thirdShiftedResult = ( maskedThird | result );

      // Mask fourth byte of pattern[1], move last bit to front and shift right
      fourth = pattern[1];
      mask = MASK_FOUR;
      maskedFourth = fourth & mask;
      maskedFourth = ( maskedFourth >> 0 );
      keepLastBit = KEEP_LAST_BIT;
      result = maskedFourth & keepLastBit;
      result = ( result << SHIFT_RESULT );
      maskedFourth = ( maskedFourth >> 1 );
      fourthShiftedResult = ( maskedFourth | result );

      // Add firstShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + firstShiftedResult;

      // Add secondShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + secondShiftedResult;   

      // Add thirdShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + thirdShiftedResult;

      // Add fourthShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + fourthShiftedResult;

    }

  }

  // Runs if offset negative
  if( offset < 0 ) {

    // Convert negative offset to positive
    offset = offset * -1;

    // Scroll horizontally for pattern[0]
    for( int i = 0; i < offset; i++ ) {

      // Mask first byte of pattern[0], move first bit to end and shift left
      first = pattern[0];
      mask = MASK_ONE;
      maskedFirst = first & mask;
      maskedFirst = ( maskedFirst >> ( BYTE_SIZE * SHIFT_THREE_BYTES ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedFirst & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedFirst = ( maskedFirst << 1 );
      maskedFirst = maskedFirst & MASK_FOUR;
      firstShiftedResult = ( maskedFirst | result );

      // Mask second byte of pattern[0], move first bit to end and shift left
      second = pattern[0];
      mask = MASK_TWO;
      maskedSecond = second & mask;
      maskedSecond = ( maskedSecond >> ( BYTE_SIZE * SHIFT_TWO_BYTES ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedSecond & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedSecond = ( maskedSecond << 1 );
      maskedSecond = maskedSecond & MASK_FOUR;
      secondShiftedResult = ( maskedSecond | result );

      // Mask third byte of pattern[0], move first bit to end and shift left
      third = pattern[0];
      mask = MASK_THREE;
      maskedThird = third & mask;
      maskedThird = ( maskedThird >> ( BYTE_SIZE * SHIFT_ONE_BYTE ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedThird & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedThird = ( maskedThird << 1 );
      maskedThird = maskedThird & MASK_FOUR;
      thirdShiftedResult = ( maskedThird | result );

      // Mask fourth byte of pattern[0], move first bit to end and shift left
      fourth = pattern[0];
      mask = MASK_FOUR;
      maskedFourth = fourth & mask;
      maskedFourth = ( maskedFourth >> 0 );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedFourth & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedFourth = ( maskedFourth << 1 );
      maskedFourth = maskedFourth & MASK_FOUR;
      fourthShiftedResult = ( maskedFourth | result );

      // Add firstShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + firstShiftedResult;

      // Add secondShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + secondShiftedResult;

      // Add thirdShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE );
      pattern[0] = pattern[0] + thirdShiftedResult;

      // Add fourthShiftedResult to pattern[0]
      pattern[0] = ( pattern[0] << BYTE_SIZE  );
      pattern[0] = pattern[0] + fourthShiftedResult;

    }

    // Scroll horizontally for pattern[1]
    for( int i = 0; i < offset; i++ ) {

      // Mask first byte of pattern[1], move first bit to end and shift left
      first = pattern[1];
      mask = MASK_ONE;
      maskedFirst = first & mask;
      maskedFirst = ( maskedFirst >> ( BYTE_SIZE * SHIFT_THREE_BYTES ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedFirst & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedFirst = ( maskedFirst << 1 );
      maskedFirst = maskedFirst & MASK_FOUR;
      firstShiftedResult = ( maskedFirst | result );

      // Mask second byte of pattern[1], move first bit to end and shift left
      second = pattern[1];
      mask = MASK_TWO;
      maskedSecond = second & mask;
      maskedSecond = ( maskedSecond >> ( BYTE_SIZE * SHIFT_TWO_BYTES ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedSecond & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedSecond = ( maskedSecond << 1 );
      maskedSecond = maskedSecond & MASK_FOUR;
      secondShiftedResult = ( maskedSecond | result );

      // Mask third byte of pattern[1], move first bit to end and shift left
      third = pattern[1];
      mask = MASK_THREE;
      maskedThird = third & mask;
      maskedThird = ( maskedThird >> ( BYTE_SIZE * SHIFT_ONE_BYTE ) );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedThird & keepFirstBit;
      result = ( result >> SHIFT_RESULT );
      maskedThird = ( maskedThird << 1 );
      maskedThird = maskedThird & MASK_FOUR;
      thirdShiftedResult = ( maskedThird | result );

      // Mask fourth byte of pattern[1], move first bit to end and shift left
      fourth = pattern[1];
      mask = MASK_FOUR;
      maskedFourth = fourth & mask;
      maskedFourth = ( maskedFourth >> 0 );
      keepFirstBit = KEEP_FIRST_BIT;
      result = maskedFourth & keepFirstBit;
      result = ( result >> SHIFT_RESULT);
      maskedFourth = ( maskedFourth << 1 );
      maskedFourth = maskedFourth & MASK_FOUR;
      fourthShiftedResult = ( maskedFourth | result );

      // Add firstShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + firstShiftedResult;

      // Add secondShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + secondShiftedResult;

      // Add thirdShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + thirdShiftedResult;
      
      // Add fourthShiftedResult to pattern[1]
      pattern[1] = ( pattern[1] << BYTE_SIZE );
      pattern[1] = pattern[1] + fourthShiftedResult;

    }

  }

}
