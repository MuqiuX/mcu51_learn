/**
 * CPU: 89C52
 * Freq: 12MHz
 */

#include "config.h"
#include "utils.h"

unsigned char number_hex_list[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void digital_tube_show(int which, int number) { 
    which--;
    which = (unsigned char)which;
    
    P2 &= 0xE3;
    P2 |= ~(which << 2);

    P0 = number_hex_list[number];
}

void main(void) {
    digital_tube_show(5, 1);

    while (1)
    {
        /* code */
    }
}