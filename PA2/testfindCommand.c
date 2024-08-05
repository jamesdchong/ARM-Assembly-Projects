/*
 * Filename: testfindCommand.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>

#include "pa2.h"
#include "test.h"

/*
 * Unit Test for findCommand.c
 *
 * int findCommand( const char * cmdString, const char * commands[] );
 *
 * Finds cmdString in array commands
 *   Returns -1 if either argument is null, or cmdString is not in commands
 *   Otherwise, return 0
 */
void testfindCommand() {

  char * badCmdString = "bad";
  const char * commands[] = COMMANDS;

  /* Test null command */
  TEST( findCommand( "clear", NULL ) == -1 );

  /* Test null cmdString */
  TEST( findCommand( NULL, commands ) == -1 );

  /* Test null command and null cmdString */
  TEST( findCommand( NULL, NULL ) == -1 );

  /* Test "set" cmdString */
  TEST( findCommand( "set", commands ) == 0 );

  /* Test bad cmdString */
  TEST( findCommand( badCmdString, commands ) == -1 );

  /* Test "scrollVertical" cmdString */
  TEST( findCommand( "scrollVertical", commands ) == 7 );

}

int main( void ) {

  fprintf( stderr, "Running tests for findCommand...\n" );
  testfindCommand();
  fprintf( stderr, "Done running tests!\n" );

  return 0;

}
