#ifndef COLOR_H
#define COLOR_H

typedef struct {
    double r, g, b;
} rgb_t;

typedef struct {
    float hue;
    float sat;
    float val;
} hsv_t;

hsv_t rgb_to_hsv(rgb_t a);

float color_rgb_dist_sq(rgb_t a, rgb_t b);
float color_rgb_dist(rgb_t a, rgb_t b);
float color_rgb_to_hue_dist(rgb_t a, rgb_t b);

#endif
