#include "stdafx.h"

#include "cv/graphics.h"

image_t gfx_create_image(int width, int height){
    uint8_t *buf = (uint8_t*) calloc(1, sizeof(rgb_t) * width * height);
    image_t image = { width, height, buf };
    return image;
}

void gfx_rect(image_t img, int x, int y, int w, int h, rgb_t c){
    for(int ay = y; ay < y + h; ay++)
        for(int ax = x; ax < x + w; ax++)
            img.buf[ay * img.width + ax] = c;
}

void gfx_circle(image_t img, int x, int y, int r, rgb_t c){
    for(int ay = y - r; ay <= y + r; ay++)
        for(int ax = x - r; ax <= x + r; ax++)
            if((ax - x) * (ax - x) + (ay - y) * (ay - y) <= r * r)
                img.buf[ay * img.width + ax] = c;
}

void gfx_convert_buf(image_t img, uint8_t *out){
    for(int i = 0; i < img.width * img.height; i++){
        out[i * 3] = (int)(img.buf[i].r * 255);
        out[i * 3 + 1] = (int)(img.buf[i].g * 255);
        out[i * 3 + 2] = (int)(img.buf[i].b * 255);
    }
}