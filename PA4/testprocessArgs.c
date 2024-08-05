/*
 * Filename: testprocessArgs.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/19
 * Sources of help: None
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <getopt.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for processArgs.c
 *
 * int processArgs( argInfo_t * info, int argc, char * argv[] );
 *
 * Processes arguments passed into the executable.
 *
 * Returns
 *  - ARG_PARSING_ERROR on error parsing flags,
 *  - REGEX_ERROR if compiling the regular expression fails,
 *  - otherwise returns 0.
 */
void testprocessArgs() {
  argInfo_t info;

  // -e flag
  memset( &info, 0, sizeof(argInfo_t) );
  int argc = 3;
  char * argv[] = { "prog", "-e", "abc*" };
  optind = 0;

  TEST( processArgs( &info, argc, argv ) == 0 );
  TEST( optind == 3 );

  // Multiple files
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 5;
  char * argv1[] = { "prog", "-e", "abc*", "file0", "file1" };
  optind = 0;

  TEST( processArgs( &info, argc, argv1 ) == 0 );
  TEST( info.flags == ARG_MULTI_FILE );
  TEST( optind == 3 );

  // help flag
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv2[] = { "prog", "--help" };
  optind = 0;

  TEST( processArgs( &info, argc, argv2 ) == 0 );
  TEST( optind == 2 );

  // -h flag invalid
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv3[] = { "prog", "-h" };
  optind = 0;

  TEST( processArgs( &info, argc, argv3 ) == ARG_PARSING_ERROR );
  TEST( optind == 2 );

  // No argument for -e flag
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 5;
  char * argv4[] = { "prog", "-e", "-n", "regex", "filename" };
  optind = 0;

  TEST( processArgs( &info, argc, argv4 ) == 0 );
  TEST( optind == 3 );
  
  // Optind out of bounds
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 1;
  char * argv5[] = { "prog" };
  optind = 0;

  TEST( processArgs( &info, argc, argv5 ) == ARG_PARSING_ERROR );
  TEST( optind == 1 );

  // Regex error
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 2;
  char * argv6[] = { "prog", "abc*[" };
  optind = 0;

  TEST( processArgs( &info, argc, argv6 ) == REGEX_ERROR );
  TEST( optind == 2 );

  // All non help flags
  memset( &info, 0, sizeof(argInfo_t) );
  argc = 8;
  char * argv7[] = { "prog", "-n", "-i", "-v", "-e", "abc", "-c", "filename" };
  optind = 0;

  TEST( processArgs( &info, argc, argv7 ) == 0 );
  TEST( optind == 7 );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for processArgs.c...\n" );
  testprocessArgs();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
