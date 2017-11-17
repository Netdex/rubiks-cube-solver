
/* Motor control abstractions. */

#ifndef MOTOR_OP_H
#define MOTOR_OP_H

#include "cube/rubik.h"

void motor_op_init();

/*
 * Rotate this face of the cube.
 * 
 * NO_SIDE does nothing.
 * NO_DIR does nothing.
 * Cannot be U or D.
 */
void motor_op_rotate_face(rubik_side_t face, rubik_dir_t dir);

/*
 * Rotate the entire cube in such a manner that the
 * given face becomes the bottom of the cube.
 * 
 * NO_SIDE does nothing.
 * 
 * U means rotate twice along up/front-plane
 * D means rotate twice along left/front-plane
 */
void motor_op_rotate_cube(rubik_side_t bottom);
#endif