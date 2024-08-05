/*
 * Filename: processArgs.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/2019
 * Sources of help: None
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "pa4.h"
#include "pa4Strings.h"

#define UNKNOWN_FLAGS '?'
#define PLUS_TWO 2

static struct option options[] = {
  { PATTERN_LONG, required_argument, NULL, PATTERN_FLAG },
  { IGNORE_CASE_LONG, no_argument, NULL, IGNORE_CASE_FLAG },
  { INVERT_MATCH_LONG, no_argument, NULL, INVERT_MATCH_FLAG },
  { COUNT_LONG, no_argument, NULL, COUNT_FLAG },
  { LINE_NUMBER_LONG, no_argument, NULL, LINE_NUMBER_FLAG },
  { HELP_LONG, no_argument, NULL, HELP_FLAG },
  { 0, 0, 0, 0 },
};

/*
 * Function Name: processArgs()
 * Function Prototype: int processArgs( argInfo_t * info, int argc
 *                                      char * argv[] );
 * Description: Populates info with a regex pattern and a bit pattern
 *              representing which flags were set in the command line arguments
 * Parameters: info - struct containing regex pattern and bit pattern
 *             argc - number of command line arguments
 *             argv - array of command line arguments
 * Side Effects: Prints error message if unknown flag passed in, populates info
 *               with regex pattern, and bit pattern representing flags passed
 *               in
 * Error Conditions: - An unrecognized flag is encountered or argv has no
 *                     pattern
 *                     argument -- return ARG_PARSING_ERROR
 *                   - regcomp() has a non-zero return value -- return
 *                     REGEX_ERROR
 * Return Value: ARG_PARSING_ERROR if an error occurred parsing the flags,
 *               REGEX_ERROR if the pattern failed to compile, 0 otherwise
 */
int processArgs( argInfo_t * info, int argc, char * argv[] ) {

  int c;

  // Sets info->flags to 0 by default
  info->flags = 0;

  // Bit pattern following e flag
  char * pattern = NULL;

  // Checks if i flag is set
  int ignoreCase = 0;

  // Checks if -e flag is set
  int hitRegexFlag = 0;

  // Parse flags using getopt
  while( ( c = getopt_long( argc, argv, SHORT_OPTS, options, NULL ) ) != -1 ) {

    switch( c ) {

      // Case for help (--help) flag
      case HELP_FLAG:
        info->flags = info->flags | ARG_HELP_FLAG;
        return 0;

      // Case to provide pattern (--regexp or -e)
      case PATTERN_FLAG:
        pattern = optarg;
        hitRegexFlag = 1;
        break;

      // Case for ignore case (--ignore-case or -i) flag
      case IGNORE_CASE_FLAG:
        info->flags = info->flags | ARG_I_FLAG;
        ignoreCase = 1;
        break;

      // Case for invert match (--invert-match or -v) flag
      case INVERT_MATCH_FLAG:
        info->flags = info->flags | ARG_V_FLAG;
        break;

      // Case for count (--count or -c) flag
      case COUNT_FLAG:
        info->flags = info->flags | ARG_C_FLAG;
        break;

      // Case for line number (--line-number or -n) flag
      case LINE_NUMBER_FLAG:
        info->flags = info->flags | ARG_N_FLAG;
        break;

      // Case to catch all unknown flags, automatically prints error message
      case UNKNOWN_FLAGS:
      default:
        return ARG_PARSING_ERROR;

    }

  }

  // If -e flag set
  if( hitRegexFlag == 1 ) {

    // More than one filename argument passed in 
    if( optind + 1 < argc ) {
      info->flags = info->flags | ARG_MULTI_FILE;
    }

  }

  // If -e flag not set
  if( hitRegexFlag == 0 ) {

    // More than one filename argument passed in
    if( optind + PLUS_TWO < argc ) {
      info->flags = info->flags | ARG_MULTI_FILE;
    }

    // Check if optind out of bounds
    if( optind >= argc ) {
      return ARG_PARSING_ERROR;
    }

    // Set pattern to first non-flag argument
    pattern = argv[optind];

    // Increment so optind is the first filename
    optind++;

  }

  // Initialize cflags bit pattern
  int cflags = REG_EXTENDED | REG_NOSUB;

  // If -i flag set, change bit pattern
  if( ignoreCase == 1 ) {
    cflags = cflags | REG_ICASE;
  }

  // Initialize rc to keep track of regcomp failing or not
  int rc = 0;

  // Compile pattern into a regex_t and store into first parameter
  rc = regcomp( &info->pattern, pattern, cflags );

  // Nonzero return value indicates error
  if( rc != 0 ) {
    return REGEX_ERROR;
  }

  return 0;

}
