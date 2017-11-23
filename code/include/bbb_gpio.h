#ifndef BBB_GPIO_H
#define BBB_GPIO_H

#define BBB_IN 0
#define BBB_OUT 1

#define BBB_LO 0
#define BBB_HI 1

/*
 * Obsolete library functions for using BBB gpios
 * Too slow to drive a stepper motor
 * */

void exp_pin(int n);
void set_dir(int n, int dir);
int read_val(int n);
void write_val(int n, int val);

#endif
