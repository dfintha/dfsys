#include "memory.h"

external void * kmemset(void *destination, char source, size_t bytes) {
    char *dst = reinterpret_cast<char *>(destination);
    for (size_t i = 0; i < bytes; ++i) {
        dst[i] = source;
    }
    return destination;
}

external void * kmemclear(void *destination, size_t bytes) {
    return kmemset(destination, 0x00, bytes);
}

external void * kmemcopy(void *destination, const void *source, size_t bytes) {
    char *dst = reinterpret_cast<char *>(destination);
    const char *src = reinterpret_cast<const char *>(source);
    for (size_t i = 0; i < bytes; ++i) {
        dst[i] = src[i];
    }
    return destination;
}

