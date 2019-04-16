#if !defined(DFSYS_MEMORY)
#define DFSYS_MEMORY

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif
    
/* set _bytes_ amount of memory to _source_ at _destination_ */
void * kmemset(void *destination, char source, size_t bytes);

/* set _bytes_ amount of memory to zero at _destination_ */
void * kmemclear(void *destination, size_t bytes);

/* copy _bytes_ amount of memory from _source_ to _destination_ */
void * kmemcopy(void *destination, void *source, size_t bytes);

#if defined(__cplusplus)
}
#endif
#endif

