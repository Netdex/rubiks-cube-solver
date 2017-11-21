#include "stdafx.h"

#include "motor.h"

void motor_init(motor m) {
    iolib_setdir(m.bank, m.pin1, BBBIO_DIR_OUT);
    iolib_setdir(m.bank, m.pin2, BBBIO_DIR_OUT);
    iolib_setdir(m.bank, m.pin3, BBBIO_DIR_OUT);
    iolib_setdir(m.bank, m.pin4, BBBIO_DIR_OUT);
    pin_low(m.bank, m.pin1);
    pin_low(m.bank, m.pin2);
    pin_low(m.bank, m.pin3);
    pin_low(m.bank, m.pin4);
}

void motor_free(motor m) {
    pin_low(m.bank, m.pin1);
    pin_low(m.bank, m.pin2);
    pin_low(m.bank, m.pin3);
    pin_low(m.bank, m.pin4);
}
void step(int step, motor m) {
    step %= 8;
    if (step < 0) step += 16;
    step %= 8;
    switch (step) {
    case 0:
        pin_low(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_high(m.bank, m.pin4);
	break;
    case 1:
        pin_low(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_high(m.bank, m.pin3);
        pin_high(m.bank, m.pin4);
	break;
    case 2:
        pin_low(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_high(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    case 3:
        pin_low(m.bank, m.pin1);
        pin_high(m.bank, m.pin2);
        pin_high(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    case 4:
        pin_low(m.bank, m.pin1);
        pin_high(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    case 5:
        pin_high(m.bank, m.pin1);
        pin_high(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    case 6:
        pin_high(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    case 7:
        pin_high(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_high(m.bank, m.pin4);
	break;
    default:
        pin_low(m.bank, m.pin1);
        pin_low(m.bank, m.pin2);
        pin_low(m.bank, m.pin3);
        pin_low(m.bank, m.pin4);
	break;
    }
}

void steps(int steps, motor m) {
    for (int i = 0; i < abs(steps); i++) {
        if (steps < 0) {
            step(-i, m);
        } else {
            step(i, m);
        }
        nsleep(DELAY);
    }
}

void q_turn(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(1024 + OVERSHOOT, m);
        steps(-OVERSHOOT, m);
    } else {
        steps(-(1024 + OVERSHOOT), m);
        steps(OVERSHOOT, m);
    }
}

void q_turn_d(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 1024 + OVERSHOOT; i++) {
        if (dir1 == DIR_CCW || dir1 == DIR_DCCW) {
            step(-i, m1);
        } else {
            step(i, m1);
        }
        if (dir2 == DIR_CCW || dir2 == DIR_DCCW) {
            step(-i, m2);
        } else {
            step(i, m2);
        }
        nsleep(DELAY);
    }
    for (int i = 0; i < OVERSHOOT; i++) {
        if (dir1 == DIR_CCW || dir1 == DIR_DCCW) {
            step(i, m1);
        } else {
            step(-i, m1);
        }
        if (dir2 == DIR_CCW || dir2 == DIR_DCCW) {
            step(i, m2);
        } else {
            step(-i, m2);
        }
        nsleep(DELAY);
    }
}

void h_turn(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(2048 + OVERSHOOT, m);
        steps(-OVERSHOOT, m);
    } else {
        steps(-(2048 + OVERSHOOT), m);
        steps(OVERSHOOT, m);
    }
}

void h_turn_d(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 2048 + OVERSHOOT; i++) {
        if (dir1 == DIR_CCW || dir1 == DIR_DCCW) {
            step(-i, m1);
        } else {
            step(i, m1);
        }
        if (dir2 == DIR_CCW || dir2 == DIR_DCCW) {
            step(-i, m2);
        } else {
            step(i, m2);
        }
        nsleep(DELAY);
    }
    for (int i = 0; i < OVERSHOOT; i++) {
        if (dir1 == DIR_CCW || dir1 == DIR_DCCW) {
            step(i, m1);
        } else {
            step(-i, m1);
        }
        if (dir2 == DIR_CCW || dir2 == DIR_DCCW) {
            step(i, m2);
        } else {
            step(-i, m2);
        }
        nsleep(DELAY);
    }
}
