#include <stdio.h>
#include "lcd.h"

void set_pin(int pin, int val) {
    if (val) {
        pin_high(8, pin);
    } else {
        pin_low(8, pin);
    }
}

void enable(lcd l) {
    pin_high(8, l.e_pin);
    nsleep(2000000);
    pin_low(8, l.e_pin);
    /*printf("Sending nibble to register %s: 0x%x\n", read_val(l.rs_pin) ? "DR" : "IR",
                     (read_val(l.d7_pin) << 3) |
                     (read_val(l.d6_pin) << 2) |
                     (read_val(l.d5_pin) << 1) |
                     read_val(l.d4_pin));*/
}

void send_nibble(lcd l, char nibble) {
    set_pin(l.d4_pin, nibble & 0x01);
    nibble >>= 1;
    set_pin(l.d5_pin, nibble & 0x01);
    nibble >>= 1;
    set_pin(l.d6_pin, nibble & 0x01);
    nibble >>= 1;
    set_pin(l.d7_pin, nibble & 0x01);
    enable(l);
}

void send_command(lcd l, char byte) {
    set_pin(l.rs_pin, 0);
    send_nibble(l, byte >> 4);
    send_nibble(l, byte & 0x0F);
    nsleep(10000000);
}

void send_data(lcd l, char byte) {
    set_pin(l.rs_pin, 1);
    send_nibble(l, byte >> 4);
    send_nibble(l, byte & 0x0F);
    nsleep(10000000);
}

void write_string(lcd l, char *str) {
    while (*str) {
        send_data(l, *str);
        str++;
    }
}

void lcd_init(lcd l) {
    iolib_setdir(8, l.rs_pin, BBBIO_DIR_OUT);
    iolib_setdir(8, l.e_pin, BBBIO_DIR_OUT);
    iolib_setdir(8, l.d4_pin, BBBIO_DIR_OUT);
    iolib_setdir(8, l.d5_pin, BBBIO_DIR_OUT);
    iolib_setdir(8, l.d6_pin, BBBIO_DIR_OUT);
    iolib_setdir(8, l.d7_pin, BBBIO_DIR_OUT);

    set_pin(l.rs_pin, 0);
    set_pin(l.e_pin, 0);
    set_pin(l.d4_pin, 0);
    set_pin(l.d5_pin, 0);
    set_pin(l.d6_pin, 0);
    set_pin(l.d7_pin, 0);

    send_command(l, 0x33);
    send_command(l, 0x32);
    send_command(l, 0x28);
    send_command(l, 0x0e);
    send_command(l, 0x01);
    send_command(l, 0x80);
}
