#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

/* DOCUMENTATION IS IN motor_op.h */

/* GPIO pinout for motors */
motor motors[] = {
    {0,0,0,0},     // F
    {0,0,0,0},     // B
    {0,0,0,0},     // L
    {0,0,0,0},     // R
    {0,0,0,0},     // L/R retract/extend
    {0,0,0,0},     // F/B retract/extend
};

void motor_op_rotate_face(rubik_side_t face, rubik_dir_t dir){
    assert(face != R_UP && face != R_DOWN);
    
}

void motor_op_rotate_cube(rubik_side_t bottom){
    
}
