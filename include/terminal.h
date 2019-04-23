#if !defined(DFSYS_TERMINAL)
#define DFSYS_TERMINAL

#include "extensions.h"
#include <stddef.h>
#include <stdint.h>

/* enumeration of the 16 standard vga colors */
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

/* initialize and reset terminal, must be called before other terminal calls */
external void kterminit();

/* set the current color of the terminal to _fg_ on _bg_ background */
external void ktermsetcol(vgacolor fg, vgacolor bg);

/* jump to the position (_x_, _y_) in the terminal buffer */
external void ktermsetpos(size_t x, size_t y);

/* print the single character _c_ to the terminal */
external void ktermprintc(char c);

/* print the string _s_ to the terminal */
external void ktermprints(const char *s);

/* print the formatted string of _format_ to the terminal */
external void ktermprintf(const char *format, ...);

#endif

