#include "bbb_gpio.h"
#include <stdio.h>
#include <stdlib.h>

void exp_pin(int n) {
    char cmd[60];
    sprintf(cmd, "echo %d > /sys/class/gpio/export", n);
    int code = system(cmd);
    if (code < 0) {
        printf("System call %s returned code %d when exporting pin %d\n", cmd, code, n);
    }
}
void set_dir(int n, int dir) {
    char cmd[60];
    sprintf(cmd, "echo %s > /sys/class/gpio/gpio%d/direction", dir ? "out" : "in", n);
    int code = system(cmd);
    if (code < 0) {
        printf("System call %s returned code %d when setting direction of pin %d\n", cmd, code, n);
    }
}
int read_val(int n) {
    char file[60];
    sprintf(file, "/sys/class/gpio/gpio%d/value", n);
    FILE *fp;
    fp = fopen(file, "l");
    int value = 0;
    int code = fscanf(fp, "%d", &value);
    if (code < 0) {
        printf("File read %s returned code %d when reading value of pin %d\n", file, code, n);
    }
    fclose(fp);
    return value;
}

void write_val(int n, int val) {
    char cmd[60];
    sprintf(cmd, "echo %d > /sys/class/gpio/gpio%d/value", val, n);
    int code = system(cmd);
    if (code < 0) {
        printf("System call %s returned code %d when writing value to pin %d\n", cmd, code, n);
    }
}
