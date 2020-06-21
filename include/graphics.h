#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stddef.h>
#include <stdint.h>

struct color_descriptor {
    uint8_t r, g, b;
};

struct pallete_info {
    struct color_descriptor *framebuffer_palette_addr;
    uint8_t framebuffer_palette_num_colors;
};

struct direct_info {
    uint8_t framebuffer_red_field_position;
    uint8_t framebuffer_red_mask_size;
    uint8_t framebuffer_green_field_position;
    uint8_t framebuffer_green_mask_size;
    uint8_t framebuffer_blue_field_position;
    uint8_t framebuffer_blue_mask_size;
};

union color_info_union {
    struct pallete_info color_info_pallete;
    struct direct_info color_info_direct;
};

union framebuffer_ptr {
    uint8_t *framebuffer8;
    uint16_t *framebuffer16;
    uint32_t *framebuffer32;
};


struct graphics_data {
    uint32_t type;
    uint32_t size;
    char *framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    union color_info_union color_info;
};

#define BLACK           {0, 0, 0}
#define BLUE            {0, 0, 170}
#define GREEN           {0, 170, 0}
#define CYAN            {0, 170, 170}
#define RED             {170, 0, 0}
#define MAGENTA         {170, 0, 170}
#define BROWN           {170, 85, 0}
#define GRAY            {170, 170, 170}
#define DARK_GRAY       {85, 85, 85}
#define BRIGHT_BLUE     {85, 85, 255}
#define BRIGHT_GREEN    {85, 255, 85}
#define BRIGHT_CYAN     {85, 255, 255}
#define BRIGHT_RED      {255, 85, 85}
#define BRIGHT_MAGENTA  {255, 85, 255}
#define YELLOW          {255, 255, 85}
#define WHITE           {255, 255, 255}

#define VMODE_INDEXED   0
#define VMODE_DIRECT    1

void init_graphics(struct graphics_data *graphics_data_ptr);
void set_pallete(struct color_descriptor *entries, size_t num_entries);

void put_pixel_direct(struct color_descriptor color, size_t x, size_t y);
void put_pixel_indexed(uint8_t index, size_t x, size_t y);

void put_pixel_direct_index(struct color_descriptor color, size_t index);

uint8_t get_video_mode();
union framebuffer_ptr get_frame_buffer();

size_t create_color(struct color_descriptor color);

#endif
