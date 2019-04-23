#if !defined(DFSYS_MEMORY)
#define DFSYS_MEMORY

#include "extensions.h"
#include <stddef.h>

/* set _bytes_ amount of memory to _source_ at _destination_ */
external void * kmemset(void *destination, char source, size_t bytes);

/* set _bytes_ amount of memory to zero at _destination_ */
external void * kmemclear(void *destination, size_t bytes);

/* copy _bytes_ amount of memory from _source_ to _destination_ */
external void * kmemcopy(void *destination, const void *source, size_t bytes);

#endif

