#include "dfsys.h"

extern "C" void kmain() {
    kterminit();
    kprints("welcome to dfsys - research version\n");
    kprints("copyright 2019 dfintha\n");
    for (int i = 0; i < 16; ++i) {
        ksetcolor(vga_black, vgacolor(i));
        kprintc(' ');
    }
    ksetcolor(vga_white, vga_black);
    kprintc('\n');
}

