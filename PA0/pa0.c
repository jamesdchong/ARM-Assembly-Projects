/*
 * Filename: pa0.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/5/2019
 * Sources of Help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "pa0.h"

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: Driver for PA0, creates an array then prints it out forwards,
 *              backwards, and forwards again. Then averages three numbers and
 *              prints out the result.
 * Parameters: argc - number of command line arguments
 *             argv - array holding the command line arguments
 * Side Effects: Prints out an array to stdout three times as well as the
 *               average of the three numbers.
 * Error Conditions:
 *   - There are an incorrect number of command line arguments.
 *   - Either one of v1, v2, or v3 is not a valid integer.
 * Return Value: EXIT_FAILURE if there was an error, EXIT_SUCCESS otherwise.
 */ 
int main( int argc, char * argv[] ) {
  --argc; // Discount the program name as part of the argument count

  // Check for the wrong number of arguments
  if ( argc != EXPECTED_ARGS ) {
    fprintf( stderr, STR_USAGE, argv[0] );
    return EXIT_FAILURE;
  }

  char * endptr;

  // Parse the first number
  errno = 0;
  int v1 = strtol( argv[FIRST_NUM_IDX], &endptr, BASE );

  if ( *endptr != '\0' || errno != 0 ) {
    fprintf( stderr, STR_ERR_NUM, argv[FIRST_NUM_IDX] );
    return EXIT_FAILURE;
  }

  // Parse the second number
  errno = 0;
  int v2 = strtol( argv[SECOND_NUM_IDX], &endptr, BASE );

  if ( *endptr != '\0' || errno != 0 ) {
    fprintf( stderr, STR_ERR_NUM, argv[SECOND_NUM_IDX] );
    return EXIT_FAILURE;
  }

  // Parse the third number
  errno = 0;
  int v3 = strtol( argv[THIRD_NUM_IDX], &endptr, BASE );

  if ( *endptr != '\0' || errno != 0 ) {
    fprintf( stderr, STR_ERR_NUM, argv[THIRD_NUM_IDX] );
    return EXIT_FAILURE;
  }

  int i;
  int average;
  int intArray[SIZE];

  // Initialize intArray with odd values starting with 1
   initArray( intArray, SIZE );

  // Print the values in the array
  for ( i = 0; i < SIZE; i++ ) {
    printf( "%d\n", intArray[i] );
  }
  printf( "\n" );

  // Print the values in intArray in reverse order
  printReversed( intArray, SIZE );
  printf( "\n" );

  // Print the values in intArray in order
  printInOrder( intArray, SIZE );
  printf( "\n" );

  // Calculate the sum of v1, v2, v3 and print out the result
  // Use the sum function to generate the sum
  average = average3( v1, v2, v3 );

  // Print out the three original numbers and the resulting sum
  printf( "The integer average of (%d + %d + %d) / %d = %d\n",
          v1, v2, v3, NUM_ELEMENTS, average );

  return EXIT_SUCCESS;
}
