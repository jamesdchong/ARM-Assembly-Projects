/*
 * Filename: buildPlot.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/16/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>

#include "pa3.h"
#include "pa3Strings.h"

#define DIVIDED_BY_TWO 2
#define MAX_PERCENT 100
#define DIVISIBLE_BY_TWO 2
#define INITIAL_UPPER_BOUND 3
#define NULL_TERMINATOR '\0'


/*
 * Function Name: buildPlot()
 * Function Prototype: void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS],
 *                                     const wordData_t * word,
 *                                     unsigned int minCount
 *                                     unsigned int maxCount );
 * Description: Populates plotArr and initialized in a way to make printing the
 *              graph trivial. 
 * Parameters: plotArr - 2d array that contains the plotted data for the word
 *                       data within word
 *             word - wordData_t struct containing the word, count array, and
 *                    the word's hash value
 *             minCount - Minimum count of all decades
 *             maxCount - Maximum count of all decades
 * Side Effects: None
 * Error Conditions: None
 * Return Value: None
 */
void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS], const wordData_t * word,
                unsigned int minCount, unsigned int maxCount ) {

  // Truncate minCount and maxCount 
  int truncMin = minCount / PERCENTAGE_FACTOR;
  int truncMax = maxCount / PERCENTAGE_FACTOR;
  unsigned int truncCount;

  // Local variables to keep track of percentage, bounds, counter
  int percentage;
  int lowerBound;
  int upperBound;
  int counter;

  // Iterates for every column
  for( int j = 0; j < PLOT_COLS - 1; j++ ) {

    // Executes when column index is even
    if( j % DIVISIBLE_BY_TWO == 0 ) {

      // All rows of even columns contain only blank space chars
      for( int i = PLOT_ROWS - 1; i >= 0; i-- ) {
        plotArr[i][j] = PLOT_SPACE_CHAR;
      }

    }

    // Executes when column index is odd
    if( j % DIVISIBLE_BY_TWO != 0 ) {

      // Truncate the value in the counts array at index j/2
      truncCount = word->counts[j / DIVIDED_BY_TWO] / PERCENTAGE_FACTOR;

      // Calculates the percentage of the truncated count
      percentage = ( ( truncCount - truncMin ) * PERCENTAGE_FACTOR ) / 
                     ( truncMax - truncMin );

      // If the truncated min and max are 0, percentage is 0
      if( truncMin == 0 && truncMax == 0 ) {
        percentage = 0;
      }

      // If the truncated min and max are the same, percentage is 100
      if( truncMin == truncMax ) {
        percentage = MAX_PERCENT;
      }

      // Reset counter, lowerBound, upperBound for each new column
      counter = 0;
      lowerBound = 0;
      upperBound = INITIAL_UPPER_BOUND;

      // Iterates for every row in j column
      for( int i = PLOT_ROWS - 1; i >= 0; i-- ) {

        // Executes if the percentage is within the lower and upper bound
        if( percentage >= lowerBound && percentage <= upperBound ) {

          // Places an 'x' at the appropriate row in the j column
          plotArr[( PLOT_ROWS - 1 ) - counter][j] = PLOT_LINE_CHAR;

        }

        // Increment lower and upper bounds by 4
        lowerBound += ROW_RESOLUTION;
        upperBound += ROW_RESOLUTION;

        // Increment counter
        counter += 1;

      }

    }

  }

  // Inserts null terminating character for each row in the very last column
  for( int i = 0; i < PLOT_ROWS; i++ ) {
    plotArr[i][PLOT_COLS - 1] = NULL_TERMINATOR;
  }

}
