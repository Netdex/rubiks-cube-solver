#include "cube_scanner.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

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

// Effectively determines how "far apart" two colours are,
// using the sum of squared differences of each component
int compare_colour(int colour1, int colour2) {
    int r1 = (colour1 >> 16) & 0xFF;
    int g1 = (colour1 >> 8) & 0xFF;
    int b1 = colour1 & 0xFF;

    int r2 = (colour2 >> 16) & 0xFF;
    int g2 = (colour2 >> 8) & 0xFF;
    int b2 = colour2 & 0xFF;

    return (r1 - r2) * (r1 - r2) +
           (g1 - g2) * (g1 - g2) +
           (b1 - b2) * (b1 - b2);
}

int determine_colour(int colour) {
    int scores[6] = {0};
    scores[0] = compare_colour(colour, WHITE);
    scores[1] = compare_colour(colour, YELLOW);
    scores[2] = compare_colour(colour, GREEN);
    scores[3] = compare_colour(colour, BLUE);
    scores[4] = compare_colour(colour, RED);
    scores[5] = compare_colour(colour, ORANGE);

    int minScore = scores[0];
    int minI = 0;
    for (int i = 1; i < 6; i++) {
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

    output[0][0] = determine_colour(c_0_0);
    output[0][1] = determine_colour(c_0_1);
    output[0][2] = determine_colour(c_0_2);

    output[1][0] = determine_colour(c_1_0);
    output[1][1] = determine_colour(c_1_1);
    output[1][2] = determine_colour(c_1_2);

    output[2][0] = determine_colour(c_2_0);
    output[2][1] = determine_colour(c_2_1);
    output[2][2] = determine_colour(c_2_2);
}
