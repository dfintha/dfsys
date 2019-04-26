#include "terminal.h"

#if defined(ARCH_X86)
uintptr_t __stack_chk_guard = 0xE2DEE396;
#elif defined(ARCH_X64)
uintptr_t __stack_chk_guard = 0x595E9FBD94FDA766;
#endif

external __attribute__((noreturn)) void __stack_chk_fail() {
    ktermprints("stack smashing detected\n");
    while (1) asm volatile ("hlt");
}
