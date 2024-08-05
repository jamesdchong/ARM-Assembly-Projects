/*
 * Filename: pa1.h
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: Given.
 */

#ifndef PA1_H
#define PA1_H

// Cool S whitespace and border characters
#define SPACE_CHAR         ' '
#define NEWLINE_CHAR       '\n'
#define FORWARD_SLASH_CHAR '/'
#define PIPE_CHAR          '|'
#define BACK_SLASH_CHAR    '\\'

// Cool S cap directions
#define DIR_UP   0
#define DIR_DOWN 1

#define BASE 10 // Used for string to int conversion
#define HALF_DIVISOR 2 // Used for dividing variable size in half
#define DOUBLE 2 // Used for doubling values

#define ARG_NUM 3 // Number of arguments
#define PROG_NAME_IDX 0 // Index of program name
#define SIZE_IDX 1 // Index of size in argv
#define CHAR_IDX 2 // Index of fillChar in argv

// Size range constants
#define MIN_SIZE 3 
#define MAX_SIZE 103 

// fillChar range constants
#define MIN_CHAR ' ' // == 32  (ASCII value, see `man ascii`)
#define MAX_CHAR '~' // == 126 (You can use these values as if they were ints)

// Used for checking if size follows 4n + 3 format
#define SIZE_OFFSET 3
#define SIZE_MULTIPLE 4

// =============================================================================
// Function prototypes
// =============================================================================
int isDividable(int dividend, int divisor);
int myRem(int dividend, int divisor);
int intervalContains(int start, int end, int value);
void outputChar(char ch);
void drawCrissCross(int size, char fillChar);
void drawCoolS(int size, char fillChar);
void outputCharNTimes(char ch, int n);
void drawCap(int size, char fillChar, int direction);

// EC prototypes
int sumOfDigits(int size, int base);

#endif // PA1_H
