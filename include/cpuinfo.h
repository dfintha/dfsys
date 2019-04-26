#if !defined(DFSYS_CPUINFO)
#define DFSYS_CPUINFO

#include "definitions.h"

/* cpu information */
typedef struct __cpuinfo {
    char manufacturer[16];
    uint8_t family;
    uint8_t model;
    uint8_t stepping;
    uint64_t flags;
} cpuinfo;

/* returns data about the current processor */
external cpuinfo kcpuinfo(void);

#endif
