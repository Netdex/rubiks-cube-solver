#include "motor.h"

void motor_init(motor m) {
    set_dir(m.pin1, BBB_OUT);
    set_dir(m.pin2, BBB_OUT);
    set_dir(m.pin3, BBB_OUT);
    set_dir(m.pin4, BBB_OUT);
    write_val(m.pin1, BBB_LO);
    write_val(m.pin2, BBB_LO);
    write_val(m.pin3, BBB_LO);
    write_val(m.pin4, BBB_LO);
}

void step(int step, motor m) {
    step %= 8;
    if (step < 0) step += 16;
    step %= 8;
    switch (step) {
    case 0:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_HI);
	break;
    case 1:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_HI);
        write_val(m.pin4, BBB_HI);
	break;
    case 2:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_HI);
        write_val(m.pin4, BBB_LO);
	break;
    case 3:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_HI);
        write_val(m.pin3, BBB_HI);
        write_val(m.pin4, BBB_LO);
	break;
    case 4:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_HI);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_LO);
	break;
    case 5:
        write_val(m.pin1, BBB_HI);
        write_val(m.pin2, BBB_HI);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_LO);
	break;
    case 6:
        write_val(m.pin1, BBB_HI);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_LO);
	break;
    case 7:
        write_val(m.pin1, BBB_HI);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_HI);
	break;
    default:
        write_val(m.pin1, BBB_LO);
        write_val(m.pin2, BBB_LO);
        write_val(m.pin3, BBB_LO);
        write_val(m.pin4, BBB_LO);
	break;
    }
}

void q_turn(motor m, int dir) {
    for (int i = 0; i < 1024; i++) {
        if (dir) {
            step(-i, m);
        } else {
            step(i, m);
        }
        nanosleep(&DELAY, NULL);
    }
}

void q_turn_d(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 1024; i++) {
        if (dir1) {
            step(-i, m1);
        } else {
            step(i, m1);
        }
        if (dir2) {
            step(-i, m2);
        } else {
            step(i, m2);
        }
        nanosleep(&DELAY, NULL);
    }
}

void h_turn(motor m) {
    for (int i = 0; i < 2048; i++) {
        step(i, m);
        nanosleep(&DELAY, NULL);
    }
}

void h_turn_d(motor m1, motor m2, int dir1, int dir2) {
    for (int i = 0; i < 2048; i++) {
        if (dir1) {
            step(-i, m1);
        } else {
            step(i, m1);
        }
        if (dir2) {
            step(-i, m2);
        } else {
            step(i, m2);
        }
        nanosleep(&DELAY, NULL);
    }
}
