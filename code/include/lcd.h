#ifndef LCD_H
#define LCD_H

#include "util/nsleep.h"
#ifndef NO_GPIO
#include <BBBiolib.h>
#endif

typedef struct {
    int rs_pin;
    int e_pin;
    int d4_pin;
    int d5_pin;
    int d6_pin;
    int d7_pin;
} lcd;

void enable(lcd l);
void send_nibble(lcd l, char nibble);
void send_command(lcd l, char byte);
void send_data(lcd l, char byte);
void write_string(lcd l, char *str);
void lcd_init(lcd l);

#endif
