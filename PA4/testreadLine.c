/*
 * Filename: testreadLine.c
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/28/19
 * Sources of help: None
 */

#include <stdio.h>
#include <string.h>

#include "pa4.h"
#include "test.h"

/*
 * Unit Test for readLine.c
 *
 * char * readLine( FILE * inputFile );
 *
 * Reads a line from inputFile, stopping at a newline or when it hits EOF
 *
 * Returns NULL if any error occurred, else a pointer to the null-terminated
 * string containing a line from the file
 */
void testreadLine() {

  char buf[BUFSIZ];
  FILE * currFile;

  // Test normal file
  snprintf( buf, BUFSIZ,
            "/home/linux/ieng6/cs30x/cs30xbh/pa4/testfiles/normalfile" );

  currFile = fopen( buf, "r" );

  TEST( strcmp( readLine( currFile ),  "This is a normal file" ) == 0 );
  TEST( strcmp( readLine( currFile ), "that has 2 lines" ) == 0 );
  TEST( readLine( currFile ) == NULL );

  fclose( currFile );

  // Test line over 128 characters
  snprintf( buf, BUFSIZ,
            "/home/linux/ieng6/cs30x/cs30xbh/pa4/testfiles/longlinefile" );

  const char * string = "This is a file that has more than one hundred and "
                        "twenty eight characters in one line without having a "
                        "new line in between each line and I am trying to type "
                        "this many words without running out of words to say";

  currFile = fopen( buf, "r" );

  TEST( strcmp( readLine( currFile ), string ) == 0 );
  TEST( strcmp( readLine( currFile ), "This is a new line" ) == 0 );

  fclose( currFile );

  // Test two normal lines, one empty line, and an EOF line
  snprintf( buf, BUFSIZ,
            "/home/linux/ieng6/cs30x/cs30xbh/pa4/testfiles/endfile" );

  currFile = fopen( buf, "r" );

  TEST( strcmp( readLine( currFile ),  "test test test" ) == 0 );
  TEST( strcmp( readLine( currFile ), "hi hello there" ) == 0 );
  TEST( strcmp( readLine( currFile ), "" ) == 0 );
  TEST( readLine( currFile ) == NULL );

  fclose( currFile );

  // Test empty file
  snprintf( buf, BUFSIZ,
            "/home/linux/ieng6/cs30x/cs30xbh/pa4/testfiles/emptyfile" );

  currFile = fopen( buf, "r" );

  TEST( readLine( currFile ) == NULL );

  fclose( currFile );

}

int main( void ) {
  
  fprintf( stderr, "Running tests for readLine.c...\n" );
  testreadLine();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
