#if !defined(DFSYS_VERSION)
#define DFSYS_VERSION

#include "definitions.h"

typedef struct __versioninfo {
    uint8_t major;
    uint8_t minor;
    uint8_t revision;
    char special;
} versioninfo;

extern const versioninfo version; 

#endif

