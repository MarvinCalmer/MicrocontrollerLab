#include <stdint.h>

// Function declarations
extern char *lcd_bin(uint8_t value);
extern char *lcd_hex(uint16_t value);
extern char *lcd_dez(uint16_t value);
extern char *AD_Volt(unsigned short val);
extern char *TempConv(unsigned short val);