#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <BBBio_lib/BBBiolib.h>

#define RS_PIN 7
#define E_PIN 8
#define D4_PIN 9
#define D5_PIN 10
#define D6_PIN 11
#define D7_PIN 12

void set_pin(int port, int pin, char val) {
    if (val) {
        pin_high(port, pin);
    } else {
        pin_low(port, pin);
    }
}

void enable() {
    set_pin(8, E_PIN, 1);
    usleep(2000);
    set_pin(8, E_PIN, 0);
    printf("Sending nibble to register %s: 0x%x\n", is_high(8, RS_PIN) ? "DR" : "IR",
                     (is_high(8, D7_PIN) << 3) |
                     (is_high(8, D6_PIN) << 2) |
                     (is_high(8, D5_PIN) << 1) |
                     is_high(8, D4_PIN));
}

void send_nibble(char nibble) {
    set_pin(8, D4_PIN, nibble & 0x01);
    nibble >>= 1;
    set_pin(8, D5_PIN, nibble & 0x01);
    nibble >>= 1;
    set_pin(8, D6_PIN, nibble & 0x01);
    nibble >>= 1;
    set_pin(8, D7_PIN, nibble & 0x01);
    enable();
}

void send_command(char byte) {
    pin_low(8, RS_PIN);
    send_nibble(byte >> 4);
    send_nibble(byte & 0x0F);
    usleep(10000);
}

void send_data(char byte) {
    pin_high(8, RS_PIN);
    send_nibble(byte >> 4);
    send_nibble(byte & 0x0F);
    usleep(10000);
}

void write_string(char *str) {
    while (*str) {
        send_data(*str);
        str++;
    }
}

void lcd_init() {
    send_command(0x33);
    send_command(0x32);
    send_command(0x28);
    send_command(0x0e);
    send_command(0x01);
    send_command(0x80);
}

int main(void) {
    iolib_init();

    iolib_setdir(8, RS_PIN, BBBIO_DIR_OUT);
    iolib_setdir(8, E_PIN, BBBIO_DIR_OUT);
    iolib_setdir(8, D4_PIN, BBBIO_DIR_OUT);
    iolib_setdir(8, D5_PIN, BBBIO_DIR_OUT);
    iolib_setdir(8, D6_PIN, BBBIO_DIR_OUT);
    iolib_setdir(8, D7_PIN, BBBIO_DIR_OUT);

    pin_low(8, RS_PIN);
    pin_low(8, E_PIN);
    pin_low(8, D4_PIN);
    pin_low(8, D5_PIN);
    pin_low(8, D6_PIN);
    pin_low(8, D7_PIN);

    lcd_init();

    write_string("RU'BF2L2R'DU2B'L");
    send_command(0xC0);
    write_string("D2L'BR2U2FB'RD'F");
    
    iolib_free();

    return 0;
}
