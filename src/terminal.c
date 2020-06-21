#include "terminal.h"

uint16_t *unicode;
struct psf_font *font;
size_t termainal_width;
size_t terminal_height;
size_t screen_width;
size_t screen_height;

size_t cursorx, cursory;

void set_psf(struct psf_font *font_ptr) {
    font = font_ptr;
    unicode = NULL;
}

void putc(char c, size_t x, size_t y, struct color_descriptor fg, struct color_descriptor bg) {
    size_t bytes_per_line = (font->width+7)/8;
    unsigned char *glyph = (unsigned char *) &font + font->header_size + (c > 0 && c < font->num_glyphs ? c : 0) * font->bytes_per_glygh;
    int offset = (y * font->height * screen_width) + (x * (font->width + 1) * 4);
    int line, mask;
    for (int i = 0; i < font->height; i++) {
        line = offset;
        mask = 1 << (font->width-1);
        for (int j = 0; j < font->width; j++) {
            put_pixel_direct_index((*glyph & mask ? fg : bg), line);
            mask >>= 1;
            line++;
        }
        glyph += bytes_per_line;
        offset += screen_width;
    }
}

void init_terminal(size_t _terminal_width, size_t _terminal_height, size_t _screen_width, size_t _screen_height) {
    termainal_width = _terminal_width;
    terminal_height = _terminal_height;
    screen_width = _screen_width;
    screen_height = _screen_height;
    cursorx = 0;
    cursory = 0;
}

void check_cursor() {
    if (cursorx >= termainal_width) {
        cursory++;
        cursorx = 0;
        if (cursory >= terminal_height) {
            cursory = 0;
        }
    }
}

void printc(char c) {
    struct color_descriptor fg = GRAY, bg = BLACK;
    if (c == '\n') {
        cursory++;
    } else if (c == '\r') {
        cursorx = 0;
    } else {
        putc(c, cursorx, cursory, fg, bg);
        cursorx++;
    }
    check_cursor();
}

void print(char *str) {
    int i = 0;
    char c = str[i];
    while (c != '\0') {
        printc(c);
        c = str[++i];
    }
}
