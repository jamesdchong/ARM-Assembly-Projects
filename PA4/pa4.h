/*
 * Filename: pa4.h
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/19
 * Sources of help: Given.
 */
#ifndef PA4_H
#define PA4_H

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

// =============================================================================
// Defined Constants
// =============================================================================

// argInfo_t flag values
#define ARG_HELP_FLAG  0x1
#define ARG_I_FLAG     0x2
#define ARG_V_FLAG     0x4
#define ARG_C_FLAG     0x8
#define ARG_N_FLAG     0x10
#define ARG_MULTI_FILE 0x80000000

// processArg() constants
#define SHORT_OPTS "e:ivcn"
#define PATTERN_FLAG 'e' 
#define IGNORE_CASE_FLAG 'i' 
#define INVERT_MATCH_FLAG 'v' 
#define COUNT_FLAG 'c' 
#define LINE_NUMBER_FLAG 'n' 
#define HELP_FLAG 'h' 

#define PATTERN_LONG "regexp" 
#define IGNORE_CASE_LONG "ignore-case"
#define INVERT_MATCH_LONG "invert-match" 
#define COUNT_LONG "count" 
#define LINE_NUMBER_LONG "line-number" 
#define HELP_LONG "help" 

#define ARG_PARSING_ERROR (-1)
#define REGEX_ERROR (-2)

// readLine() constants
#define NEWLINE_CHAR '\n'

// XXX: DO NOT CHANGE LINE_BUFFER_SIZE BELOW
// Define buffer size to be 128 unless it has been defined already by gcc -D
#ifndef LINE_BUFFER_SIZE
#define LINE_BUFFER_SIZE 128
#endif

// EC --dereference-recursive constants
#define ARG_R_FLAG     0x20
#define EC_SHORT_OPTS "e:ivcnR"
#define RECURSIVE_FLAG 'R'
#define RECURSIVE_LONG "dereference-recursive"

#define MAX_PATH_LEN 4096

// =============================================================================
// Struct Definition (DO NOT EDIT)
// =============================================================================

/*
 * Struct to hold command-line argument information.
 */
struct argInfo {
  // The compiled PATTERN argument (which may come after -e).
  regex_t pattern;

  // Which of -i, -v, -c, -n, --help were set? Are there multiple files?
  int flags;
};
typedef struct argInfo argInfo_t;

// =============================================================================
// Function Prototypes (DO NOT EDIT)
// =============================================================================

int processArgs( argInfo_t * info, int argc, char * argv[] );
int lineMatchesRegex( const regex_t * pattern, const char * line );
int lineShouldBePrinted( const char * line, const argInfo_t * info );
char * readLine ( FILE * inputFile );
FILE * openFile( const char * filename );
int search( const argInfo_t * info, const char * filename );
int count( const argInfo_t * info, const char * filename );

// EC prototypes.
int recursiveGrep( argInfo_t * info, const char * path );
int recursiveGrepDir( argInfo_t * info, const char * dirpath );

#endif // PA4_H
