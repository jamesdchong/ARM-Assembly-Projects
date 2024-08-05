/*
 * Filename: initArray.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/5/2019
 * Sources of Help: None
 */

#include "pa0.h"

/*
 * Function Name: initArray()
 * Function Prototype: void initArray( int array[], int length );
 * Description: Initializes values in an array to be odd integers starting 
 *              from 1
 * Parameters: array - the array to initialize
 *             length - the length of the array
 * Side Effects: Initializes the values of the array
 * Error Conditions: None
 * Return Value: None
 */
void initArray( int array[], int length ) {
  int i = 0;

  while ( i < length ) {
    array[i] = ODD_MULTIPLIER * i + 1;
    i++;
  }
}
