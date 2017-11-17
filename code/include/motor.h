#ifndef MOTOR_H
#define MOTOR_H

#ifndef NO_GPIO
#include <BBBiolib.h>
#endif
#include "util/nsleep.h" 

#define DELAY 750000

typedef struct {
    int pin1;
    int pin2;
    int pin3;
    int pin4;
} motor;

void motor_init(motor m);
void step(int step, motor m);
void q_turn(motor m, int dir);
void q_turn_d(motor m1, motor m2, int dir1, int dir2);
void h_turn(motor m);
void h_turn_d(motor m1, motor m2, int dir1, int dir2);

#endif
