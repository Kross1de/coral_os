/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#pragma once

struct terminal
{
        uint32_t *base; // framebuffer
        uint32_t width_pixel;
        uint32_t height_pixel;
        uint32_t pitch;
        uint32_t width_char;
        uint32_t height_char;
        uint32_t cursor_x;
        uint32_t cursor_y;
        uint32_t color_foreground;
        uint32_t color_background;
};

void terminal_init(struct terminal *term, uint32_t *framebuffer, uint32_t width, uint32_t height, uint32_t pitch);
void terminal_putc(struct terminal *term, char c);
void terminal_print(struct terminal *term, const char *str, size_t len);
void terminal_scroll_up(struct terminal *term);