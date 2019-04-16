#include "memory.h"

extern "C" void * kmemset(void *destination, char source, size_t bytes) {
    char *dst = reinterpret_cast<char *>(destination);
    for (size_t i = 0; i < bytes; ++i) {
        dst[i] = source;
    }
    return destination;
}

extern "C" void * kmemclear(void *destination, size_t bytes) {
    return kmemset(destination, 0x00, bytes);
}

extern "C" void * kmemcopy(void *destination, void *source, size_t bytes) {
    char *dst = reinterpret_cast<char *>(destination);
    char *src = reinterpret_cast<char *>(source);
    for (size_t i = 0; i < bytes; ++i) {
        dst[i] = src[i];
    }
    return destination;
}

