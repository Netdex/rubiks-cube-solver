#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

/* DOCUMENTATION IS IN motor_op.h */

/* GPIO pinout for motors */

motor motors[] = {
        {43,44,45,46},     // F
        {7,8,9,10},        // B
        {39,40,41,42},     // L
        {15,16,17,18},     // R
        {35,36,37,38},     // L/R retract/extend
        {11,12,13,14},     // F/B retract/extend
};

void motor_op_rotate_face(rubik_side_t face, rubik_dir_t dir){
    assert(face != R_UP && face != R_DOWN);
    
}

void motor_op_rotate_cube(rubik_side_t bottom){
    
}
