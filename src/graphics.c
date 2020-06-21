#include "graphics.h"

union framebuffer_ptr framebuffer;
uint32_t width;
uint32_t height;
uint32_t pitch;
uint8_t bpp;
struct color_descriptor *pallete;
uint8_t video_mode;
struct direct_info color_info;

static void init_pallete(struct color_descriptor *pallet_ptr, size_t pallete_size) {
    struct color_descriptor colors[] = {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        GRAY,
        DARK_GRAY,
        BRIGHT_BLUE,
        BRIGHT_GREEN,
        BRIGHT_CYAN,
        BRIGHT_RED,
        BRIGHT_MAGENTA,
        YELLOW,
        WHITE
    };
    pallete = pallet_ptr;

    if (pallete_size > 16) {
        pallete_size = 16;
    }

    set_pallete(colors, 16);
}

void copy_direct_info(struct direct_info *src, struct direct_info *dst) {
    dst->framebuffer_red_mask_size = src->framebuffer_red_mask_size;
    dst->framebuffer_red_field_position = src->framebuffer_red_field_position;
    dst->framebuffer_green_mask_size = src->framebuffer_green_mask_size;
    dst->framebuffer_green_field_position = src->framebuffer_green_field_position;
    dst->framebuffer_blue_mask_size = src->framebuffer_blue_mask_size;
    dst->framebuffer_blue_field_position = src->framebuffer_blue_field_position;
}

void init_graphics(struct graphics_data *graphics_data_ptr) {
    framebuffer.framebuffer8 = graphics_data_ptr->framebuffer_addr;
    width = graphics_data_ptr->framebuffer_width;
    height = graphics_data_ptr->framebuffer_height;
    pitch = graphics_data_ptr->framebuffer_pitch;
    bpp = graphics_data_ptr->framebuffer_bpp;
    video_mode = graphics_data_ptr->framebuffer_type;
    if (video_mode == VMODE_INDEXED) {
        init_pallete(graphics_data_ptr->color_info.color_info_pallete.framebuffer_palette_addr, graphics_data_ptr->color_info.color_info_pallete.framebuffer_palette_num_colors);
    } else {
        copy_direct_info(&graphics_data_ptr->color_info.color_info_direct, &color_info);
    }
}

void set_pallete(struct color_descriptor *entries, size_t num_entries) {
    for (size_t i = 0; i < num_entries; i++) {
        pallete[i] = entries[i];
    }
}

void put_pixel_direct(struct color_descriptor color, size_t x, size_t y) {
    if (x < width && y < height) {
        size_t index = y * pitch + ((x * bpp) / 8);
        put_pixel_direct_index(color, index);
    }
}

void put_pixel_direct_index(struct color_descriptor color, size_t index) {
    if (bpp < 8) {
        framebuffer.framebuffer8[index] = create_color(color);
    } else if (bpp < 16) {
        framebuffer.framebuffer16[index] = create_color(color);
    } else {
        framebuffer.framebuffer32[index] = create_color(color);
    }
}

size_t create_mask(size_t size) {
    size_t mask = 0x00;
    for (size_t i = 0; i < size; i++) {
        mask |= 0x01;
        mask <<= 0x01;
    }
    return mask;
}

size_t create_color(struct color_descriptor color) {
    size_t color_int = 0;
    size_t red = (color.r & create_mask(color_info.framebuffer_red_mask_size)) << color_info.framebuffer_red_field_position;
    size_t green = (color.g & create_mask(color_info.framebuffer_green_mask_size)) << color_info.framebuffer_green_field_position;
    size_t blue = (color.b & create_mask(color_info.framebuffer_blue_mask_size)) << color_info.framebuffer_blue_field_position;
    color_int = color_int | red | green | blue;
    return color_int;
}

void put_pixel_indexed(uint8_t pallete_index, size_t x, size_t y) {
    if (x < width && y < height) {
        size_t index = y * pitch + ((x * bpp) / 8);
        framebuffer.framebuffer8[index] = pallete_index;
    }
}

uint8_t get_video_mode() {
    return video_mode;
}

union framebuffer_ptr get_frame_buffer() {
    return framebuffer;
}
