#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "stdint.h"
#include "cv/color.h"

typedef struct {
    int width;
    int height;
    rgb_t *buf;
} image_t;

image_t gfx_create_image(int width, int height);
void gfx_rect(image_t img, int x, int y, int w, int h, rgb_t c);
void gfx_circle(image_t img, int x, int y, int r, rgb_t c);
void gfx_line(image_t img, int x1, int y1, int x2, int y2, rgb_t c);

void gfx_convert_buf(image_t img, uint8_t *out);

#endif