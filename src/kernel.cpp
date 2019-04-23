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
    ktermprints("\n welcome to dfsys - research version\n");
    ktermprintf(" version %u.%u.%u-%c \n",
    			kversion.major, kversion.minor,
    			kversion.revision, kversion.special);
    ktermprints(" copyright 2019 dfintha\n\n");

    ktermsetcol(vga_black, vga_green);
    const cpuinfo info = kcpuinfo();
    ktermprintf("\n cpu information\n"
    			"   manufacturer: %s\n"
    			"   family:       %u\n"
    			"   model:        %u\n"
    			"   stepping:     %u\n\n",
    			info.manufacturer, info.family, info.model, info.stepping);
    
    ktermsetcol(vga_white, vga_red);
    ktermprints("\n you can turn off your computer now :D\n\n");
    ktermsetcol(vga_white, vga_black);
}
