#include "stdafx.h"

#include "cv/color.h"

// Converts a value in RGB colorspace to one in HSV colorspace, for easier color recognition
hsv_t rgb_to_hsv(rgb_t a) {
    double rp = a.r;
    double gp = a.g;
    double bp = a.b;

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

    hsv_t ret = {hue, sat, val};
    return ret;
}

// Calculates the squared distance of each component R, G, and B, to tell how different two colors
// are. However, this algorithm is not actually very good for rubik's cube faces, so it is not used
float color_rgb_dist_sq(rgb_t a, rgb_t b){
    //return (a.r - b.r) * (a.r - b.r) + (a.g - b.g) * (a.g - b.g) + (a.b - b.b) * (a.b - b.b);
    return (a.r - b.r) * (a.r - b.r) + (a.g - b.g) * (a.g - b.g) + (a.b - b.b) * (a.b - b.b);
}

// Takes in two RGB colors and calculates their distance in hue: which is very accurate for determining
// what color a sticker on a rubik's cube is. There is a special case when both colors are white
// (saturation less than 0.25), because the hue is inconsistent for white faces (colorless)
float color_rgb_to_hue_dist(rgb_t a, rgb_t b) {
    hsv_t ha = rgb_to_hsv(a);
    hsv_t hb = rgb_to_hsv(b);

    if (ha.sat <= 0.25 && hb.sat <= 0.25) {
        return 0;
    }
    else if (min(ha.sat, hb.sat) <= 0.25 && max(ha.sat, hb.sat) > 0.25) {
        return 9999;
    }

    return min(fabs(ha.hue - hb.hue),
           min(fabs(360 + ha.hue - hb.hue),
               fabs(ha.hue - hb.hue - 360)));
}

// The unsquared distance in RGB colorspace
float color_rgb_dist(rgb_t a, rgb_t b){
    return sqrt(color_rgb_dist_sq(a,b));
}
