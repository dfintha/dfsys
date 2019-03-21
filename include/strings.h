#if !defined(DFSYS_STRINGS)
#define DFSYS_STRINGS

#include "definitions.h"

#if defined(__cplusplus)
extern "C" {
#endif

size_t kstrlen(const char *string);
int    kstrcmp(const char *first, const char *second);
char * kstrchr(const char *haystack, char needle);
char * kstrstr(const char *haystack, const char *needle);

char * kstrcpy(char *destination, const char *source);
char * kstrcat(char *destination, const char *source);

#if defined(__cplusplus)
}
#endif
#endif

