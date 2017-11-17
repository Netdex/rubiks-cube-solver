
/* Motor control abstractions. */

#ifndef MOTOR_OP_H
#define MOTOR_OP_H

#include "cube/rubik.h"

/*
 * Rotate this face of the cube.
 * Cannot be U or D.
 */
void motor_rotate_face(rubik_side_t face);

/*
 * Rotate the entire cube in such a manner that the
 * given face becomes the bottom of the cube.
 * 
 * Cannot be U or D.
 */
void motor_rotate_cube(rubik_side_t bottom);
#endif