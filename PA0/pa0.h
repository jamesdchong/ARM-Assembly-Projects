/*
 * Filename: pa0.h
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/5/2019
 * Sources of Help: Given.
 */

/*
 * XXX Only add constants to this file.
 * DO NOT EDIT FUNCTION PROTOTYPES.
 */

#ifndef PA0_H
#define PA0_H

/* 
 * Constant values to be used in PA0
 */
#define SIZE 15  // The size of the array
#define BASE 10 // Base of input numbers
#define ODD_MULTIPLIER 2 // Used for initializing the values in the array
#define NUM_ELEMENTS 3 // Used for printing the average message

// Command line arguments
#define EXPECTED_ARGS 3
#define FIRST_NUM_IDX 1
#define SECOND_NUM_IDX 2
#define THIRD_NUM_IDX 3

#define STR_USAGE \
  "\nUsage: %s v1 v2 v3\n" \
  "Prints arrays forward and in reverse, prints the average of v1, v2, v3\n\n" \

#define STR_ERR_NUM "\n\t%s is not a valid integer\n\n"

/*
 * Function prototypes for the C and assembly routines used in PA0
 */
void initArray( int array[], int length );
void printReversed( int array[], int length );
void printInOrder( int array[], int length );
int average3( int a, int b, int c );

#endif /* PA0_H */

