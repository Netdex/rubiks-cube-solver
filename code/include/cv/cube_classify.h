#ifndef CUBE_CLASSIFY_H
#define CUBE_CLASSIFY_H

#include "cube/rubik.h"
#include "cv/color.h"

/*
 * Creates an RGB color matrix from an rgb image
 */
void cube_classify_face_image_argb(uint8_t *image, int bpp, int width, int height, int x1, int y1, int x2, int y2, rgb_t col_mat[3][3]);

/*
 * Builds a cube from average color values of cube,
 * clustering with k-memes
 * 
 * Face order is U, R, F, D, L, B
 * Face orientation is defined in "ckociemba/facelets.h"
 */
rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3]);

#endif