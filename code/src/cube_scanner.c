#include "cube_scanner.h"
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const hsv_colour WHITE = {0.0, 0.0, 1.0};
const hsv_colour YELLOW = {60.0, 1.0, 1.0};
const hsv_colour GREEN = {120.0, 1.0, 1.0};
const hsv_colour BLUE = {240.0, 1.0, 1.0};
const hsv_colour RED = {0.0, 1.0, 1.0};
const hsv_colour ORANGE = {20.0, 1.0, 1.0};

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

// Returns the most common colour in 0-5 of the pixels in the given region
int colour_of_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height) {
    int colour_freq[6] = {0};
    int maxFreq = 0;
    int maxI = -1;
    for (int x = centre_x - width / 2; x < centre_x + width / 2; x++) {
        for (int y = centre_y - height / 2; y < centre_y + height / 2; y++) {
            int r = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 3];
            int g = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 2];
            int b = image[y * image_w * image_bpp + x * image_bpp + image_bpp - 1];
            hsv_colour h = rgb_to_hsv(r, g, b);

            int col = determine_colour(h);
            colour_freq[col]++;
            if (colour_freq[col] > maxFreq) {
                maxFreq = colour_freq[col];
                maxI = col;
            }
        }
    }
    
    return maxI;
}

int compare_colour(hsv_colour colour1, hsv_colour colour2) {
    return min(fabs(colour1.hue - colour2.hue),
           min(fabs(colour1.hue + 360 - colour2.hue),
               fabs(colour1.hue - 360 - colour2.hue)));
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

    output[0][0] = colour_of_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[0][1] = colour_of_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[0][2] = colour_of_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_0_CENTRE, BOX_WIDTH, BOX_HEIGHT);

    output[1][0] = colour_of_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[1][1] = colour_of_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[1][2] = colour_of_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_1_CENTRE, BOX_WIDTH, BOX_HEIGHT);

    output[2][0] = colour_of_region(rgb_image, width, height, bpp, X_0_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[2][1] = colour_of_region(rgb_image, width, height, bpp, X_1_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);
    output[2][2] = colour_of_region(rgb_image, width, height, bpp, X_2_CENTRE, Y_2_CENTRE, BOX_WIDTH, BOX_HEIGHT);
}
