#include "stdafx.h"

#include "cv/color.h"

hsv_colour rgb_to_hsv(int r, int g, int b) {
    double rp = r / 255.0;
    double gp = g / 255.0;
    double bp = b / 255.0;

    double Cmax = max(rp, max(gp, bp));
    double Cmin = min(rp, min(gp, bp));

    double delta = Cmax - Cmin;

    double hue = 0;
    
    if (delta > 0.00001) {
        if (Cmax == rp) {
            double term = (gp - bp) / delta;
            while (term >= 6.0) term -= 6.0;
            hue = 60 * term;
        } else if (Cmax == gp) {
            hue = 60 * (((bp - rp) / delta) + 2);
        } else {
            hue = 60 * (((rp - gp) / delta) + 4);
        }
    }

    if (hue < 0.0) {
        hue += 360.0;
    }

    double sat = 0;
    if (Cmax != 0) {
        sat = delta / Cmax;
    }
    
    double val = Cmax;

    hsv_colour ret = {hue, sat, val};
    return ret;
}

float color_rgb_dist_sq(rgb_t a, rgb_t b){
    return (a.r - b.r) * (a.r - b.r) + (a.g - b.g) * (a.g - b.g) + (a.b - b.b) * (a.b - b.b);
}

float color_rgb_dist(rgb_t a, rgb_t b){
    return sqrt(color_rgb_dist_sq(a,b));
}