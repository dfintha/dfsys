#if !defined(DFSYS_VERSION)
#define DFSYS_VERSION

#include <stdint.h>

/* structure containing version info for the kernel */
typedef struct __versioninfo {
    uint8_t major;
    uint8_t minor;
    uint8_t revision;
    char special;
} versioninfo;

/* global version information */
extern const versioninfo kversion; 

#endif

