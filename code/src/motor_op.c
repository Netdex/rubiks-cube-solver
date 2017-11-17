#include "stdafx.h"
#include "motor_op.h"
#include "motor.h"

motor motors[] = {
    {0,0,0,0},     // F
    {0,0,0,0},     // B
    {0,0,0,0},     // L
    {0,0,0,0},     // R
    {0,0,0,0},     // L/R release
    {0,0,0,0},     // F/B release
};

void motor_rotate_face(rubik_side_t face){
    assert(face != R_UP && face != R_DOWN);

    switch(face){
        case R_FRONT:
        break;
        case R_BACK:
        break;
        case R_LEFT:
        break;
        case R_RIGHT:
        break;
    }
}

void motor_rotate_cube(rubik_side_t bottom){
    assert(bottom != R_UP && bottom != R_DOWN);
}
