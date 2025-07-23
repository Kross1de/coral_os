/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#include "terminal.h"
#include "../std.h"
#include "../library/font.h"

void terminal_init(struct terminal *term, uint32_t *framebuffer, uint32_t width, uint32_t height, uint32_t pitch)
{
        term->base = framebuffer;
        term->width_pixel = width;
        term->height_pixel = height;
        term->pitch = pitch;
        term->width_char = width / LIB_FONT_WIDTH_pixel;
        term->height_char = height / LIB_FONT_HEIGHT_pixel;
        term->cursor_x = 0;
        term->cursor_y = 0;
        term->color_foreground = STD_COLOR_GREEN_light;
        term->color_background = 0x00101010; // dark

        // clear the screen
        for (uint32_t y = 0; y < height; y++)
        {
                for (uint32_t x = 0; x < width; x++)
                {
                        term->base[y * (pitch / 4) + x] = term->color_background;
                }
        }
}

void terminal_scroll_up(struct terminal *term)
{
        uint32_t line_size = LIB_FONT_HEIGHT_pixel * (term->pitch / 4);
        for (uint32_t y = 0; y < term->height_pixel - LIB_FONT_HEIGHT_pixel; y++)
        {
                for (uint32_t x = 0; x < term->width_pixel; x++)
                {
                        term->base[y * (term->pitch / 4) + x] = term->base[(y + LIB_FONT_HEIGHT_pixel) * (term->pitch / 4) + x];
                }
        }
        // clear the last line
        for (uint32_t y = term->height_pixel - LIB_FONT_HEIGHT_pixel; y < term->height_pixel; y++)
        {
                for (uint32_t x = 0; x < term->width_pixel; x++)
                {
                        term->base[y * (term->pitch / 4) + x] = term->color_background;
                }
        }
}

void terminal_putc(struct terminal *term, char c)
{
        if (c == '\n')
        {
                term->cursor_x = 0;
                term->cursor_y++;
                if (term->cursor_y >= term->height_char)
                {
                        terminal_scroll_up(term);
                        term->cursor_y = term->height_char - 1;
                }
        }
        else if (c >= 0x20 && c <= 0x7e)
        {
                uint32_t *pixel = term->base + (term->cursor_y * LIB_FONT_HEIGHT_pixel * (term->pitch / 4)) + (term->cursor_x * LIB_FONT_WIDTH_pixel);
                lib_font(LIB_FONT_FAMILY_ROBOTO_MONO, &c, 1, term->color_foreground, pixel, term->pitch / 4, LIB_FONT_ALIGN_left);
                term->cursor_x++;
                if (term->cursor_x >= term->width_char)
                {
                        term->cursor_x = 0;
                        term->cursor_y++;
                        if (term->cursor_y >= term->height_char)
                        {
                                terminal_scroll_up(term);
                                term->cursor_y = term->height_char - 1;
                        }
                }
        }
}

void terminal_print(struct terminal *term, const char *str, size_t len)
{
        for (size_t i = 0; i < len; i++)
                terminal_putc(term, str[i]);
}