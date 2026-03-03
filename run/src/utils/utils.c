#include <stdio.h>
#include "utils.h"

unsigned char loop(unsigned char value, int d, int n) {
    int mask_n = sizeof(value) * 8 - n;

    if (d) {
        return (value >> n) | (value << mask_n);
    } else {
        return (value << n) | (value >> mask_n);
    }
}