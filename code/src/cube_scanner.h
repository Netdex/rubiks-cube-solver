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
#define WHITE 0xffffff  // 0
#define YELLOW 0xa8a061 // 1
#define GREEN 0x006e39  // 2
#define BLUE 0x00248D   // 3
#define RED 0x921618    // 4
#define ORANGE 0xB94D27 // 5

void scan_face(char* imageLoc, int output[3][3]);
int average_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height);
int compare_colour(int colour1, int colour2);
int determine_colour(int colour);

#endif
