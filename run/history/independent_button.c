/**
 * CPU: 89C52
 * Freq: 12MHz
 * 
 * 本次通过独立按键控制LED灯的移位，
 * 根据电路图，原理是当按键按下的时候，
 * 金属片连接了按钮两端，
 * 使得寄存器对应位置于另一端带同样的负电
 */

#include <STC/STC89C5xRC.H>
#include <INTRINS.H>
#include <stdio.h>

unsigned char loop(unsigned char value, int d, int n) {
    int mask_n = sizeof(value) * 8 - n;

    if (d) {
        return (value >> n) | (value << mask_n);
    } else {
        return (value << n) | (value >> mask_n);
    }
}

void Delay20ms(void) {
    unsigned char data i, j;

    i = 39;
    j = 230;
    do {
        while (--j)
            ;
    } while (--i);
}

void main(void) {
    P2 = 0xFE; // 初始化

    while (1) {
        if (P30 == 0) { // 读取一整个按下到放开按钮的一个按压过程
            Delay20ms();
            while (P30 == 0);
            Delay20ms();

            P2 = loop(P2, 0, 1);
        }

        if (P31 == 0) {
            Delay20ms();
            while (P31 == 0);
            Delay20ms();

            P2 = loop(P2, 1, 1);
        }
    }
}