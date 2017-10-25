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

#define BOX_WIDTH 60
#define BOX_HEIGHT 60

#define WIDTH 640
#define HEIGHT 360

// Colour definitions
typedef struct {
    double hue;
    double sat;
    double val;
} hsv_colour;

extern const hsv_colour WHITE;
extern const hsv_colour YELLOW;
extern const hsv_colour GREEN;
extern const hsv_colour BLUE;
extern const hsv_colour RED;
extern const hsv_colour ORANGE;

void scan_face(char* imageLoc, int output[3][3]);
hsv_colour rgb_to_hsv(int r, int g, int b);
int colour_of_region(uint8_t* image, int image_w, int image_h, int image_bpp, int centre_x, int centre_y, int width, int height);
int compare_colour(hsv_colour colour1, hsv_colour colour2);
int determine_colour(hsv_colour colour);

#endif
