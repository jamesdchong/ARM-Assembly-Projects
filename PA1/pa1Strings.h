/*
 * Filename: pa1Strings.h
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/13/2019
 * Sources of help: Given.
 */

#ifndef PA1_STRINGS_H
#define PA1_STRINGS_H

// Usage message
#define COOL_S_USAGE \
    "\nUsage: %s size fillChar\n" \
    "  size: equal to the maximum width of the Cool S\n" \
    "    -- must be in the interval [%d, %d]\n" \
    "    -- must be of the form (size = 4n + 3)\n" \
    "         where n is some integer\n" \
    "  fillChar: used for filling in the Cool S\n" \
    "    -- must be a single character\n" \
    "    -- must be within the ASCII range [%d, %d]\n\n"

// Error strings for size
#define SIZE_CONVERT_ERR \
    "\nError when converting size (%s) into base %d"
#define SIZE_NOT_INT_ERR \
    "\nError: size must be an integer in base %d\n\n"
#define SIZE_RANGE_ERR \
    "\nError: size must be within the range [%d, %d]\n\n"
#define SIZE_FORMAT_ERR \
    "\nError: size must be an integer of the format 4n + 3\n\n"

// Error strings for fillChar
#define SINGLE_CHAR_ERR \
    "\nError: fillChar must be a single char\n\n"
#define CHAR_RANGE_ERR \
    "\nError: fillChar must be within ASCII range [%d, %d]\n\n"

#endif // PA1_STRINGS_H
