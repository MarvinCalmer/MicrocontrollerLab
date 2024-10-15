#include "lcd.h"
#include "tests.h"

char *lcd_bin(uint8_t value) {
    static char text_string[9];  // 8 bits + 1 null terminator
    unsigned char asc[] = "01";  // ASCII for binary digits

    for (int i = 0; i < 8; i++) {
        text_string[7 - i] = asc[(value >> i) & 1];  // Shifting bits and extracting 0/1
    }
    text_string[8] = 0;  // Null terminator
    return text_string;
}

char *lcd_hex(uint16_t value) {
    static char text_string[5];  // 4 hex digits + 1 null terminator
    unsigned char asc[] = "0123456789ABCDEF";

    text_string[0] = asc[(value >> 12) & 0xF];  // Extract highest 4 bits
    text_string[1] = asc[(value >> 8) & 0xF];   // Extract next 4 bits
    text_string[2] = asc[(value >> 4) & 0xF];   // Extract next 4 bits
    text_string[3] = asc[value & 0xF];          // Extract lowest 4 bits
    text_string[4] = 0;  // Null terminator
    return text_string;
}

char *lcd_dez(uint16_t value) {
    static char text_string[6];  // Max 5 digits + 1 null terminator
    unsigned char asc[] = "0123456789";

    text_string[0] = asc[(value / 10000) % 10];
    text_string[1] = asc[(value / 1000) % 10];
    text_string[2] = asc[(value / 100) % 10];
    text_string[3] = asc[(value / 10) % 10];
    text_string[4] = asc[value % 10];
    text_string[5] = 0;  // Null terminator
    return text_string;
}