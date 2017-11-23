#include "stdafx.h"

#include "motor.h"

/*
 *
 * Utility functions for driving stepper motors using the Beaglebone's GPIOs
 * */


// Initialize motors by setting direction to output and value to low
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

// Turns off the motors to stop drawing current and stop holding position
void motor_free(motor m) {
    pin_low(m.bank, m.pin1);
    pin_low(m.bank, m.pin2);
    pin_low(m.bank, m.pin3);
    pin_low(m.bank, m.pin4);
}

// Performs a single step on the given motor. Calling repeatedly with incrementing numbers
// will go through the correct phases to rotate the stepper motor
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

// Performs multiple steps on the motor, sign of steps indicates direction
// positive = clockwise, negative = counterclockwise
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

// Does a quarter turn (90 degrees) of the given motor, in the given direction
// Also does "overshoot", turning it a bit too far then going back to correct for 
// the wiggle in the stepper motors
void q_turn(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(1024 + OVERSHOOT, m);
        steps(-OVERSHOOT, m);
    } else {
        steps(-(1024 + OVERSHOOT), m);
        steps(OVERSHOOT, m);
    }
}

// Performs a quarter turn with no overshoot
void q_turn_nos(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(1024, m);
    } else {
        steps(-1024, m);
    }
}

// Performs a quarter turn on two motors simultaneously
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

// No overshoot version of q_turn_d
void q_turn_d_nos(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 1024; i++) {
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
}

// Does a half (180 degree) turn
void h_turn(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(2048 + OVERSHOOT, m);
        steps(-OVERSHOOT, m);
    } else {
        steps(-(2048 + OVERSHOOT), m);
        steps(OVERSHOOT, m);
    }
}

// No overshoot version
void h_turn_nos(motor m, int dir) {
    if (dir == DIR_CW || dir == DIR_DCW) {
        steps(2048, m);
    } else {
        steps(-2048, m);
    }
}

// Does a half turn on two motors simultaneously
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

// Special no overshoot version of h_turn_d for cube rotations (
void h_turn_d_nos(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 2048; i++) {
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
}
