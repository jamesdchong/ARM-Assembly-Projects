/*
 * Filename: printPlot.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"

#define NEW_LINE "\n"
#define MAX_PERCENT 100

/*
 * Function Name: printPlot()
 * Function Prototype: void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS],
 *                                     unsigned int minCount
 *                                     unsigned int maxCount );
 * Description: Prints the graph that has been previously initialized by
 *              buildPlot() to stdout.
 * Parameters: plotArr - 2d array that contains the plotted data for the word
 *                       data within word
 *             minCount - Minimum count of all decades
 *             maxCount - Maximum count of all decades
 * Side Effects: Prints the plotArr array as a graph to stdout
 * Error Conditions: None
 * Return Value: None
 */
void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], unsigned int minCount,
                unsigned int maxCount ) {

  // Initialize percentage to keep track of row we are on while looping,
  //   starting at 100
  unsigned int percentage = MAX_PERCENT;

  // Print new line at beginning
  printf( NEW_LINE );

  // Print plots for percentage 100, along with maxCount on y-axis
  printf( STR_PLOT_ROW_BOUND, maxCount, MAX_PERCENT, plotArr[0] );

  // Decrement percent by 4 after printing percent 100
  percentage -= ROW_RESOLUTION;

  // Print plots for each percentage between 0 and 100, decrementing by 4 each
  //   time
  for( int i = 1; i < PLOT_ROWS - 1; i++ ) {
    printf( STR_PLOT_ROW, percentage, plotArr[i] );
    percentage -= ROW_RESOLUTION;
  }

  // Print plots for percentage 0, along with minCount on y-axis
  printf( STR_PLOT_ROW_BOUND, minCount, 0, plotArr[PLOT_ROWS - 1] );

  // Print x-axis
  printf( STR_PLOT_X_AXIS );
  
  // Print new line at end
  printf( NEW_LINE );

}
