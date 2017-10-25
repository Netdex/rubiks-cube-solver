#ifndef CUBE_SCANNER_H
#define CUBE_SCANNER_H

#include <stdint.h>

// Region definitions
#define X_0_CENTRE 200
#define Y_0_CENTRE 50

#define X_1_CENTRE 320
#define Y_1_CENTRE 169

#define X_2_CENTRE 442
#define Y_2_CENTRE 290

#define BOX_WIDTH 80
#define BOX_HEIGHT 80

#define WIDTH 640
#define HEIGHT 360

// Colour definitions
//#define WHITE 0xffffff  // 0
//#define YELLOW 0xa8a061 // 1
//#define GREEN 0x006e39  // 2
//#define BLUE 0x00248D   // 3
//#define RED 0x921618    // 4
//#define ORANGE 0xB94D27 // 5

typedef struct {
    double hue;
    double sat;
    double val;
} hsv_colour;

//const hsv_colour WHITE_MIN = {0.0, 0.0, 0.85};
//const hsv_colour WHITE_MAX = {360.0, 0.15, 1.0};
//
//const hsv_colour YELLOW_MIN = {53.0, 0.5, 0.75};
//const hsv_colour YELLOW_MAX = {75.0, 1.0, 1.0};
//
//const hsv_colour GREEN_MIN = {90.0, 0.5, 0.4};
//const hsv_colour GREEN_MAX = {170.0, 1.0, 1.0};
//
//const hsv_colour BLUE_MIN = {200.0, 0.5, 0.4};
//const hsv_colour BLUE_MAX = {270.0, 1.0, 1.0};
//
//const hsv_colour RED_MIN = {340.0, 0.5, 0.4};
//const hsv_colour RED_MAX = {370.0, 1.0, 1.0};
//
//const hsv_colour ORANGE_MIN = {18.0, 0.5, 0.4};
//const hsv_colour ORANGE_MAX = {45.0, 1.0, 1.0};

const hsv_colour WHITE = {0.0, 0.0, 1.0};
const hsv_colour YELLOW = {60.0, 1.0, 1.0};
const hsv_colour GREEN = {120.0, 1.0, 1.0};
const hsv_colour BLUE = {240.0, 1.0, 1.0};
const hsv_colour RED = {0.0, 1.0, 1.0};
const hsv_colour ORANGE = {32.0, 1.0, 1.0};

void scan_face(char* imageLoc, int output[3][3]);
int average_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height);
int compare_colour(hsv_colour colour1, hsv_colour colour2);
int determine_colour(hsv_colour colour);

#endif
