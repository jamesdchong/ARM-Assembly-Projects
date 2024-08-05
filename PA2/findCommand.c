/*
 * Filename: findCommand.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 4/26/2019
 * Sources of help: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa2.h"
#include "pa2Strings.h"

#define COMMANDS_LENGTH 10

/*
 * Function Name: findCommand()
 * Function Prototype: int findCommand( const char * cmdString,
 *                                      const char * commands[] );
 * Description: Look for the given cmdString in commands and return its index
 * Parameters: cmdString - command string passed in
 *             commands[] - array of strings containing commands
 * Side Effects: None 
 * Error Conditions: cmdString is null, commands is null, cmdString is not in
 *                   commands
 * Return Value: -1 if either argument is null or if cmdString is not found.
 *               Otherwise, return index of command
 */
int findCommand( const char * cmdString, const char * commands[] ) {

  // Initialize contains to zero
  int contains = 0;

  // Return -1 if cmdString is null
  if( cmdString == NULL ) {
    return -1;
  }

  // Return if commands is null
  if( commands == NULL ) {
    return -1;
  }

  // Loop through each command in commands array
  for( int i = 0; i < COMMANDS_LENGTH; i++ ) {

    // If the cmdString is the commands string at index i, set contains to i
    //   and break the loop
    if( !strcmp( cmdString, commands[i] ) ) {

      contains = i;
      break;

    } else {

      // Else set contains to -1
      contains = -1;
    }
  }

  return contains;  // Return

}
