#include "kernel.h"

external void kmain() {
    kterminit();
    ktermsetcol(vga_white, vga_blue);
    ktermprints("\n welcome to dfsys - research version\n");
    ktermprintf(" version %u.%u.%u-%c\n",
                kversion.major,
                kversion.minor,
                kversion.revision,
                kversion.special);
    ktermprints(" copyright 2019 dfintha\n\n");

    ktermsetcol(vga_black, vga_green);
    const cpuinfo info = kcpuinfo();
    ktermprintf("\n cpu information\n");
    ktermprintf("   manufacturer: %s\n", info.manufacturer);
    ktermprintf("   family:       %u\n", info.family);
    ktermprintf("   model:        %u\n", info.model);
    ktermprintf("   stepping:     %u\n\n", info.stepping);

    ktermsetcol(vga_white, vga_red);
    ktermprints("\n you can turn off your computer now :D\n\n");
    ktermsetcol(vga_white, vga_black);
}
