#ifndef TERMINAL_H
#define TERMINAL_H

#define PSF_FONT_MAGIC 0x864ab572

#include <stdint.h>
#include <stddef.h>

#include "graphics.h"

void init_terminal(size_t terminal_width, size_t terminal_height, size_t _screen_width, size_t _screen_height);

struct psf_font {
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t flags;
    uint32_t num_glyphs;
    uint32_t bytes_per_glygh;
    uint32_t height;
    uint32_t width;
};

void set_psf(struct psf_font *font_ptr);

void putc(char c, size_t x, size_t y, struct color_descriptor fg, struct color_descriptor bg);
void printc(char c);
void print(char *str);

#endif
