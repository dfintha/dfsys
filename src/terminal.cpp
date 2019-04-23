#include "strings.h"
#include "terminal.h"
#include <stdarg.h>

constexpr const size_t vga_width = 80;
constexpr const size_t vga_height = 25;

namespace terminal {
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t *buffer;
}

internal uint8_t imkcolor(vgacolor fg, vgacolor bg) {
    return fg | bg << 4;
}

internal uint16_t imkentry(unsigned char c, uint8_t colors) {
    return static_cast<uint16_t>(c) | static_cast<uint16_t>(colors << 8);
}

internal void iputc(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * vga_width + x;
    terminal::buffer[index] = imkentry(c, color);
}

internal void iscroll() {
    const size_t total = vga_width * vga_height;
    for (size_t i = vga_width; i < total; ++i) {
        terminal::buffer[i - vga_width] = terminal::buffer[i];
    }
    const size_t laststart = (vga_width * vga_height) - vga_width;
    for (size_t i = laststart; i < total; ++i) {
        terminal::buffer[i] = imkentry(' ', terminal::color);
    }
    ktermsetpos(0, vga_height - 1);
}

external void kterminit() {
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

external void ktermprintc(char c) {
    if (c != '\n') {
        iputc(c, terminal::color, terminal::column, terminal::row);
    }

    if (++terminal::column == vga_width || c == '\n') {
        const size_t diff = vga_width - terminal::column + 1;
        for (size_t i = 0; i < diff; ++i) {
            const size_t column = terminal::column + i - 1;
            iputc(' ', terminal::color, column, terminal::row);
        }

        terminal::column = 0;

        if (++terminal::row == vga_height) {
            --terminal::row;
            iscroll();
        }
    }
}

external void ktermprints(const char *s) {
    while (*s != '\0')
        ktermprintc(*s++);
}

external void ktermsetcol(vgacolor fg, vgacolor bg) {
    terminal::color = imkcolor(fg, bg);
}

external void ktermsetpos(size_t x, size_t y) {
    terminal::column = x;
    terminal::row = y;
}

external void ktermprintf(const char *format, ...) {
    char buffer[2048];
    va_list args;
    va_start(args, format);
    kstrformatv(buffer, format, args);
    va_end(args);
    ktermprints(buffer);
}
