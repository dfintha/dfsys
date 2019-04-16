#if !defined(DFSYS_MEMORY)
#define DFSYS_MEMORY

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif
    
void * kmemset(void *destination, char source, size_t bytes);
void * kmemclear(void *destination, size_t bytes);
void * kmemcopy(void *destination, void *source, size_t bytes);

#if defined(__cplusplus)
}
#endif
#endif

