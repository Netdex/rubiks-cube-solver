
/* Motor control abstractions. */

#ifndef MOTOR_OP_H
#define MOTOR_OP_H

#include "cube/rubik.h"

void motor_op_init();

/*
 * Rotate this face of the cube.
 * 
 * @param face  The face to rotate
 * If face == NO_SIDE, do nothing.
 * Cannot be R_UP or R_DOWN
 * 
 * @param dir   The direction to rotate that face
 * If dir == NO_DIR, do nothing.
 */
void motor_op_rotate_face(rubik_side_t face, rubik_dir_t dir);

/*
 * Rotate the entire cube in such a manner that the
 * given face becomes the bottom of the cube.
 * 
 * @param bottom    After the cube rotation, this face becomes the new bottom.
 * ie. R_LEFT would rotate the entire cube along the left/up-plane, 
 * so that the left face is now on the bottom.
 * 
 * If bottom == NO_SIDE, do nothing.
 * 
 * Special cases:
 * R_UP means rotate twice along up/front-plane     (the same as doing R_FRONT twice)
 * R_DOWN means rotate twice along up/left-plane (the same as doing R_LEFT twice)
 * A rotation in the front/left-plane requires 3 separate rotations.
 */
void motor_op_rotate_cube(rubik_side_t bottom);
#endif
