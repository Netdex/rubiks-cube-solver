#include "lcd.h"

void enable(lcd l) {
    write_val(l.e_pin, BBB_HI);
    nsleep(2000000);
    write_val(l.e_pin, BBB_LO);
    /*printf("Sending nibble to register %s: 0x%x\n", read_val(l.rs_pin) ? "DR" : "IR",
                     (read_val(l.d7_pin) << 3) |
                     (read_val(l.d6_pin) << 2) |
                     (read_val(l.d5_pin) << 1) |
                     read_val(l.d4_pin));*/
}

void send_nibble(lcd l, char nibble) {
    write_val(l.d4_pin, nibble & 0x01);
    nibble >>= 1;
    write_val(l.d5_pin, nibble & 0x01);
    nibble >>= 1;
    write_val(l.d6_pin, nibble & 0x01);
    nibble >>= 1;
    write_val(l.d7_pin, nibble & 0x01);
    enable(l);
}

void send_command(lcd l, char byte) {
    write_val(l.rs_pin, BBB_LO);
    send_nibble(l, byte >> 4);
    send_nibble(l, byte & 0x0F);
    nsleep(10000000);
}

void send_data(lcd l, char byte) {
    write_val(l.rs_pin, BBB_HI);
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
    send_command(l, 0x33);
    send_command(l, 0x32);
    send_command(l, 0x28);
    send_command(l, 0x0e);
    send_command(l, 0x01);
    send_command(l, 0x80);
}
