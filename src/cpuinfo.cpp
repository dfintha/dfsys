#include "cpuinfo.h"
#include "memory.h"

internal void icpuid(uint32_t *eax, uint32_t *ebx,
                     uint32_t *ecx, uint32_t *edx) {
    asm volatile ("cpuid" :
                  "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) :
                  "0" (*eax), "2" (*ecx));
}

internal void icpumanufacturer(cpuinfo *destination) {
    uint32_t eax = 0x00;
    uint32_t ebx = 0x00;
    uint32_t ecx = 0x00;
    uint32_t edx = 0x00;
    icpuid(&eax, &ebx, &ecx, &edx);

    kmemcopy(destination->manufacturer + 0, (const void *) &ebx, 4);
    kmemcopy(destination->manufacturer + 4, (const void *) &edx, 4);
    kmemcopy(destination->manufacturer + 8, (const void *) &ecx, 4);
    destination->manufacturer[12] = '\0';
}

internal void icpuparams(cpuinfo *destination) {
    uint32_t eax = 0x01;
    uint32_t ebx = 0x00;
    uint32_t ecx = 0x00;
    uint32_t edx = 0x00;
    icpuid(&eax, &ebx, &ecx, &edx);

    destination->family = ((eax >> 8) & 0x0F);
    destination->model = ((eax >> 4) & 0x0F);
    destination->stepping = (eax & 0x0F);

    if (destination->family == 0x06 || destination->family == 0x0F) {
        const uint8_t xmodel = (eax >> 16) & 0x0F;
        destination->model = (xmodel << 4) + destination->model;
    }

    if (destination->family == 0x0F) {
        const uint8_t xfamily = (eax >> 20) & 0xFF;
        destination->family = destination->family + xfamily;
    }

    destination->flags = (uint64_t(ecx) << 32) + edx;
}

external cpuinfo kcpuinfo(void) {
    cpuinfo result;
    icpumanufacturer(&result);
    icpuparams(&result);
    return result;
}

