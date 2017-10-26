#include "stdafx.h"

#include "cv/graphics.h"

image_t gfx_create_image(int width, int height){
    rgb_t *buf = (rgb_t*) calloc(1, sizeof(rgb_t) * width * height);
    image_t image = { width, height, buf };
    return image;
}

void gfx_rect(image_t img, int x, int y, int w, int h, rgb_t c){
    for(int ay = max(0, y); ay < min(img.height, y + h); ay++)
        for(int ax = max(0, x); ax < min(img.width, x + w); ax++)
            img.buf[ay * img.width + ax] = c;
}

void gfx_circle(image_t img, int x, int y, int r, rgb_t c){
    for(int ay = max(0, y - r); ay < min(img.height, y + r); ay++)
        for(int ax = max(0, x - r); ax < min(img.width, x + r); ax++)
            if((ax - x) * (ax - x) + (ay - y) * (ay - y) <= r * r)
                img.buf[ay * img.width + ax] = c;
}

void gfx_line(image_t img, int x1, int y1, int x2, int y2, rgb_t c){
    float m = (float)(y2 - y1) / (x2 - x1);
    if(x1 > x2){
        int t = x1;
        x1 = x2;
        x2 = t;
        t = y1;
        y1 = y2;
        y2 = t;
    }
    for(int x = max(0, x1); x < min(img.width, x2); x++){
        int y = (int)(m * x) + y1;
        if(y >= 0 && y < img.height)
            img.buf[y * img.width + x] = c;
    }
}

void gfx_convert_buf(image_t img, uint8_t *out){
    for(int i = 0; i < img.width * img.height; i++){
        out[i * 3] = (int)(img.buf[i].r * 255);
        out[i * 3 + 1] = (int)(img.buf[i].g * 255);
        out[i * 3 + 2] = (int)(img.buf[i].b * 255);
    }
}