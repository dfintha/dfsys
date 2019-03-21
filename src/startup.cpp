#include "dfsys.h"

extern "C" void kmain() {
    kterminit();
    ktermprints("welcome to dfsys - research version\n");
    ktermprints("copyright 2019 dfintha\n");
    for (int i = 0; i < 16; ++i) {
        ktermsetcol(vga_black, vgacolor(i));
        ktermprintc(' ');
    }
    ktermsetcol(vga_white, vga_black);
    ktermprintc('\n');
}

