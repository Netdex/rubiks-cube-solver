#ifndef COLOR_H
#define COLOR_H

typedef struct {
    double r, g, b;
} rgb_t;

typedef struct {
    float hue;
    float sat;
    float val;
} hsv_colour;

hsv_colour rgb_to_hsv(int r, int g, int b);

float color_rgb_dist_sq(rgb_t a, rgb_t b);
float color_rgb_dist(rgb_t a, rgb_t b);

#endif