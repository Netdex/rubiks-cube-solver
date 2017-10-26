#ifndef CUBE_SCANNER_H
#define CUBE_SCANNER_H

#include <stdint.h>

#include "cv/color.h"

// Region definitions
#define X_0_CENTRE 200
#define Y_0_CENTRE 50

#define X_1_CENTRE 320
#define Y_1_CENTRE 169

#define X_2_CENTRE 442
#define Y_2_CENTRE 290

#define BOX_WIDTH 60
#define BOX_HEIGHT 60

#define WIDTH 640
#define HEIGHT 360

// Colour definitions

static const hsv_colour WHITE = {0.0, 0.0, 1.0};
static const hsv_colour YELLOW = {60.0, 1.0, 1.0};
static const hsv_colour GREEN = {120.0, 1.0, 1.0};
static const hsv_colour BLUE = {240.0, 1.0, 1.0};
static const hsv_colour RED = {0.0, 1.0, 1.0};
static const hsv_colour ORANGE = {20.0, 1.0, 1.0};

void scan_face(char* imageLoc, int output[3][3]);

int colour_of_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height);
int compare_colour(hsv_colour colour1, hsv_colour colour2);
int determine_colour(hsv_colour colour);

#endif
