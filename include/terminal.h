#if !defined(DFSYS_TERMINAL)
#define DFSYS_TERMINAL

#include <stddef.h>
#include <stdint.h>

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
void ktermsetcol(vgacolor fg, vgacolor bg);
void ktermsetpos(size_t x, size_t y); 
void ktermprintc(char c);
void ktermprints(const char *s);

#if defined(__cplusplus)
}
#endif
#endif

