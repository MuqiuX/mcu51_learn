/**
 * CPU: 89C52
 * Freq: 12MHz
 * 
 * 本程序通过改变寄存器P2的值实现LED的流水灯，
 * 在LED的电路图中显示一侧接VCC正极，
 * 通过向P2寄存器对应位置写入0制造低电平即可点亮对应LED
 */

#include <INTRINS.H>
#include <STC/STC89C5xRC.H>
#include <stdio.h>

void Delay500ms(void) {
    unsigned char data i, j, k;

    _nop_();
    i = 4;
    j = 205;
    k = 187;
    do {
        do {
            while (--k)
                ;
        } while (--j);
    } while (--i);
}

unsigned char right_loop(unsigned char value, int n) {
    int bits = sizeof(value) * 8;
    return (value >> n) | (value << (bits - n));
}

void main(void) {
    P2 = 0xFE; // 初始化

    do {
        Delay500ms();
        P2 = right_loop(P2, 1);
    } while (1);
}