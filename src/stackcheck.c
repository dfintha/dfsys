#include "terminal.h"
#include <stdint.h>

#if (UINT32_MAX == UINTPTR_MAX)
uintptr_t __stack_chk_guard = 0xE2DEE396;
#else
uintptr_t __stack_chk_guard = 0x595E9FBD94FDA766;
#endif

external __attribute__((noreturn)) void __stack_chk_fail() {
    ktermprints("stack smashing detected\n");
    while (1) asm volatile ("hlt");
}
