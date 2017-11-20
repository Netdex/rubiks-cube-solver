
/* Motor control abstractions. */

#ifndef MOTOR_OP_H
#define MOTOR_OP_H

#include "cube/rubik.h"

#define ARM_FB      4
#define ARM_LR      5

#define G_VERT      0
#define G_HORIZ     1

#define ARM_RETRACT 0
#define ARM_PARTIAL 1
#define ARM_EXTEND  2

#define MOTOR_F     0 
#define MOTOR_B     1
#define MOTOR_L     2
#define MOTOR_R     3
#define MOTOR_FB    4
#define MOTOR_LR    5

/* rotate face, update state */
void motor_op_rot(int motor, int op); 
/* rotate two faces simultaneously */
void motor_op_rots(int motor1, int op1, int motor2, int op2);
/* retract/extend grabber arms, update state */
void motor_op_arm_move(int arm, int op);
/* retract/extend both grabber arms simulatenously, update state */
void motor_op_arms_move(int arm1, int op1, int arm2, int op2);

void motor_op_init();
void motor_op_reset();

void motor_op_perform_sequence(rubik_sequence_t seq);

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
void motor_op_rotate_face(int fmotor, int op);
void motor_op_rotate_faces(rubik_side_t f1, rubik_dir_t d1,
                            rubik_side_t f2, rubik_dir_t d2);
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
