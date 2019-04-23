#include "kernel.h"

#if (UINT32_MAX == UINTPTR_MAX)
uintptr_t __stack_chk_guard = 0xE2DEE396;
#else
uintptr_t __stack_chk_guard = 0x595E9FBD94FDA766;
#endif

external __attribute__((noreturn)) void __stack_chk_fail() {
    ktermprints("stack smashing detected\n");
    while (true) asm volatile ("hlt");
}

external void kmain() {
    kterminit();
    ktermsetcol(vga_white, vga_blue);
    ktermprints("welcome to dfsys - research version\n");
    ktermprints("copyright 2019 dfintha\n\n");
    ktermsetcol(vga_white, vga_black);
    ktermprintc('\n');
}

