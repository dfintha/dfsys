#if !defined(DFSYS_STRING)
#define DFSYS_STRING

#include "extensions.h"
#include <stddef.h>

/* writes _number_ to zero-terminated string at _destination_ in base _radix_ */
external void kstritoa(char *destination, unsigned long number, int radix);

/* returns the length of the zero-terminated string _string_ */
external size_t kstrlen(const char *string);

/* compares two zero-terminated strings, returns result, see strlen */
external int kstrcmp(const char *first, const char *second);

/* compares two zero-terminated strings with the maximum length of _bytes_ */
external int kstrncmp(const char *first, const char *second, size_t bytes);

/* copies a zero-terminated string from _source_ to _destination_ */
external char * kstrcpy(char *destination, const char *source);

/* copies a maximum of _bytes_ characters from _source_ to _destination_ */
external char * kstrncpy(char *destination, const char *source, size_t bytes);

/* appends zero-terminated string _source_ to _destination_ */
external char * kstrcat(char *destination, const char *source);

#endif

