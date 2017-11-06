#ifndef MOTOR_H
#define MOTOR_H

#include "bbb_gpio.h"
#include <time.h>

static const struct timespec DELAY = {0, 750000L};

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
