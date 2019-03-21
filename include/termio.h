#if !defined(DFSYS_TERMIO)
#define DFSYS_TERMIO

#include "definitions.h"

typedef enum __vgacolor {
    vga_black        = 0,
    vga_blue         = 1,
    vga_green        = 2,
    vga_cyan         = 3,
    vga_red          = 4,
    vga_magenta      = 5,
    vga_brown        = 6,
    vga_lightgray    = 7,
    vga_darkgray     = 8,
    vga_lightblue    = 9,
    vga_lightgreen   = 10,
    vga_lightcyan    = 11,
    vga_lightred     = 12,
    vga_lightmagenta = 13,
    vga_lightbrown   = 14,
    vga_white        = 15
} vgacolor;

#if defined(__cplusplus)
extern "C" {
#endif

void kterminit();
void ksetcolor(vgacolor fg, vgacolor bg);
void ktermpos(size_t x, size_t y); 
void kprintc(char c);
void kprints(const char *s);

#if defined(__cplusplus)
}
#endif
#endif

