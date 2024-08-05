/*
 * Filename: pa4Strings.h
 * Author: James Chong
 * UserId: cs30xbh
 * Date: 5/26/19
 * Sources of help: Given.
 */

#ifndef PA4_STRINGS_H
#define PA4_STRINGS_H

// Command-line argument messages
#define STR_USAGE \
  "\n" \
  "Usage: %s [OPTION]... PATTERN [FILE]...\n" \
  "       %s -e PATTERN [OPTION]... [FILE]...\n" \
  "OPTIONS\n" \
  "  -e PATTERN, --regexp=PATTERN  use PATTERN for matching\n" \
  "  -i, --ignore-case             ignore case distinctions\n" \
  "  -v, --invert-match            select non-matching lines\n" \
  "  -c, --count                   print only a count of matching lines per " \
  "FILE\n" \
  "  -n, --line-number             print line number with output lines\n" \
  "  --help                        display this help text and exit\n\n"

#define STR_SHORT_USAGE \
  "\nUsage: %s [OPTION]... PATTERN [FILE]...\n" \
  "Try '%s --help' for more information.\n\n"

#define STR_ERR_REGEX "\n\tInvalid regular expression.\n\n"

// readLine()
#define STR_ERR_MEM_EXCEEDED "\n\tMemory limit exceeded.\n"

// openFile()
#define STR_OPEN_READ "r"
#define STR_ERR_OPEN_FILE "mygrep: %s: %s\n"

// search() / count()
#define STR_STDIN "-"

#define STR_FILENAME "%s:"
#define STR_LINENUM "%u:"

#define STR_LINE "%s\n"
#define STR_COUNT "%u\n"

// EC
#define STR_EC_USAGE \
  "\n" \
  "Usage: %s [OPTION]... PATTERN [FILE]...\n" \
  "       %s -e PATTERN [OPTION]... [FILE]...\n" \
  "OPTIONS\n" \
  "  -e PATTERN, --regexp=PATTERN  use PATTERN for matching\n" \
  "  -i, --ignore-case             ignore case distinctions\n" \
  "  -v, --invert-match            select non-matching lines\n" \
  "  -c, --count                   print only a count of matching lines per " \
  "FILE\n" \
  "  -n, --line-number             print line number with output lines\n" \
  "  -R, --dereference-recursive   recurse on directories, following " \
  "symlinks\n" \
  "  --help                        display this help text and exit\n\n"

#define STR_CURR_DIR "."
#define STR_PARENT_DIR ".."
#define STR_PATH_JOIN "%s/%s"

#endif // PA4_STRINGS_H
