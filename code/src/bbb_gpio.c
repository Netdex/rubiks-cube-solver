#include "bbb_gpio.h"
#include <stdio.h>
#include <stdlib.h>

void exp_pin(int n) {
    char cmd[60];
    sprintf(cmd, "echo %d > /sys/class/gpio/export", n);
    system(cmd);
}
void set_dir(int n, int dir) {
    char cmd[60];
    sprintf(cmd, "echo %s > /sys/class/gpio/gpio%d/direction", dir ? "out" : "in", n);
    system(cmd);
}
int read_val(int n) {
    char file[60];
    sprintf(file, "/sys/class/gpio/gpio%d/value", n);
    FILE *fp;
    fp = fopen(file, "l");
    int value = 0;
    fscanf(fp, "%d", &value);
    fclose(fp);
    return value;
}

void write_val(int n, int val) {
    char cmd[60];
    sprintf(cmd, "echo %d > /sys/class/gpio%d/direction", val, n);
    system(cmd);
}
