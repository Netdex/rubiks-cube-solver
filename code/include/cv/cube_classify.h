#ifndef CUBE_CLASSIFY_H
#define CUBE_CLASSIFY_H

#include "cube/rubik.h"
#include "cv/color.h"

/*
 * Builds a cube from average color values of cube,
 * clustering with k-memes
 * 
 * Face order is U, R, F, D, L, B
 * Face orientation is defined in "ckociemba/facelets.h"
 */
rubik_cube_t cube_classify_from_colors(rgb_t colors[6][3][3]);

#endif