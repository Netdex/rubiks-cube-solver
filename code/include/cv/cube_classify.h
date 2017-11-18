#ifndef CUBE_CLASSIFY_H
#define CUBE_CLASSIFY_H

#include "cube/rubik.h"
#include "cv/color.h"

/*
 * Read image from webcam
 * @param width     Return parameter for width
 * @param height    Return parameter for height
 * @param bpp       Return parameter for pixel stride
 * @return          Pointer to bitmap
 */
uint8_t* cube_classify_read_webcam(int *width, int *height, int *bpp);

/*
 * Creates an RGB color matrix from an rgb image
 */
void cube_classify_face_image_argb(uint8_t *image, int bpp, int width, int height, int x1, int y1, int x2, int y2, float pad, rgb_t col_mat[3][3]);

rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3]);

#endif