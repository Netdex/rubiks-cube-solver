#include "cube_scanner.h"
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

double max(double a, double b) {
    if (a > b) return a;
    return b;
}

double min(double a, double b) {
    if (a < b) return a;
    return b;
}

hsv_colour rgb_to_hsv(int r, int g, int b) {
    double rp = r / 255.0;
    double gp = g / 255.0;
    double bp = b / 255.0;

    double Cmax = max(rp, max(gp, bp));
    double Cmin = min(rp, min(gp, bp));

    double delta = Cmax - Cmin;

    double hue = 0;
    
    if (Cmax == rp) {
        double term = (gp - bp) / delta;
        while (term >= 6.0) term -= 6.0;
        hue = 60 * term;
    } else if (Cmax = gp) {
        hue = 60 * (((bp - rp) / delta) + 2);
    } else {
        hue = 60 * (((rp - gp) / delta) + 4);
    }

    double sat = 0;
    if (Cmax != 0) {
        sat = delta / Cmax;
    }
    
    double val = Cmax;

    hsv_colour ret = {hue, sat, val};
    return ret;
}

int average_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height) {
    long long r_sum = 0;
    long long g_sum = 0;
    long long b_sum = 0;
    for (int x = centre_x - width / 2; x < centre_x + width / 2; x++) {
        for (int y = centre_y - height / 2; y < centre_y + height / 2; y++) {
            int r = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 3];
            int g = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 2];
            int b = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 1];

            r_sum += r;
            g_sum += g;
            b_sum += b;
        }
    }
    r_sum /= width * height;
    g_sum /= width * height;
    b_sum /= width * height;
    
    return ((int) r_sum << 16) | ((int) g_sum << 8) | (int) b_sum;
}

int compare_colour(hsv_colour colour1, hsv_colour colour2) {
    return min(fabs(colour1.hue - colour2.hue), fabs(colour1.hue + 360 - colour2.hue));
}

int determine_colour(hsv_colour colour) {
    if (colour.sat <= 0.15 && colour.val >= 0.85) return 0;
    int scores[6] = {0};
    scores[1] = compare_colour(YELLOW, colour);
    scores[2] = compare_colour(GREEN, colour);
    scores[3] = compare_colour(BLUE, colour);
    scores[4] = compare_colour(RED, colour);
    scores[5] = compare_colour(ORANGE, colour);
    
    int minScore = scores[1];
    int minI = 1;

    for (int i = 2; i < 6; i++) {
        if (scores[i] < minScore) {
            minScore = scores[i];
            minI = i;
        }
    }
    return minI;
}

void scan_face(char* imageLoc, int output[3][3]) {
    int width = 0, height = 0, bpp = 0;
    uint8_t* rgb_image = stbi_load(imageLoc, &width, &height, &bpp, 3);

    if (width != WIDTH || height != HEIGHT) {
        printf("Scanner warning: image input is %dx%d not %dx%d\n", width, height, WIDTH, HEIGHT);
    }

    int c_0_0 = average_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_0_1 = average_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_0_2 = average_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);

    int c_1_0 = average_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_1_1 = average_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_1_2 = average_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);

    int c_2_0 = average_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_2_1 = average_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    int c_2_2 = average_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);

    //output[0][0] = determine_colour(c_0_0);
    //output[0][1] = determine_colour(c_0_1);
    //output[0][2] = determine_colour(c_0_2);
//
    //output[1][0] = determine_colour(c_1_0);
    //output[1][1] = determine_colour(c_1_1);
    //output[1][2] = determine_colour(c_1_2);
//
    //output[2][0] = determine_colour(c_2_0);
    //output[2][1] = determine_colour(c_2_1);
    //output[2][2] = determine_colour(c_2_2);
}
