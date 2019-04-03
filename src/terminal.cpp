#include "terminal.h"

constexpr const size_t vga_width = 80;
constexpr const size_t vga_height = 25;

namespace terminal {
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t *buffer;
}

static inline uint8_t imkcolor(vgacolor fg, vgacolor bg) {
    return fg | bg << 4;
}

static inline uint16_t imkentry(unsigned char c, uint8_t colors) {
    return static_cast<uint16_t>(c) | static_cast<uint16_t>(colors << 8);
}

static inline void iprintc(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * vga_width + x;
    terminal::buffer[index] = imkentry(c, color);
}

extern "C" void kterminit() {
    terminal::row = 0;
    terminal::column = 0;
    terminal::color = imkcolor(vga_white, vga_black);
    terminal::buffer = reinterpret_cast<uint16_t *>(0xB8000);

    for (size_t y = 0; y < vga_height; ++y) {
        for (size_t x = 0; x < vga_width; ++x) {
            const size_t index = y * vga_width + x;
            terminal::buffer[index] = imkentry(' ', terminal::color);
        }
    }
}

extern "C" void ktermprintc(char c) {
    if (c != '\n')
        iprintc(c, terminal::color, terminal::column, terminal::row);

    if (++terminal::column == vga_width || c == '\n') {
        terminal::column = 0;
        if (++terminal::row == vga_height) {
            terminal::row = 0;
        }
    }
}

extern "C" void ktermprints(const char *s) {
    while (*s != '\0')
        ktermprintc(*s++);
}

extern "C" void ktermsetcol(vgacolor fg, vgacolor bg) {
    terminal::color = imkcolor(fg, bg);
}

extern "C" void ktermsetpos(size_t x, size_t y) {
    terminal::column = x;
    terminal::row = y;
}
