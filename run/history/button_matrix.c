/**
 * CPU: 89C52
 * Freq: 12MHz
 * 
 * 实现了按钮矩阵的扫描
 */

#include "LCD1602.h"
#include "config.h"
#include "utils.h"

void Delay20ms(void) {
    unsigned char data i, j;

    i = 234;
    j = 115;
    do {
        while (--j)
            ;
    } while (--i);
}

unsigned int KeyValue = 0;

void matrix_button_down() {

    P1 = 0x0f;

    if (P1 != 0x0f) {
        Delay20ms(); // 第一次消抖
        if (P1 != 0x0f) { // 判断是否还是按下
            // 测试列
            P1 = 0X0F;
            switch (P1) {
            case (0X07):
                KeyValue = 1;
                break;
            case (0X0b):
                KeyValue = 2;
                break;
            case (0X0d):
                KeyValue = 3;
                break;
            case (0X0e):
                KeyValue = 4;
                break;
            }
            // 测试行
            P1 = 0XF0;
            switch (P1) {
            case (0X70):
                KeyValue = KeyValue;
                break;
            case (0Xb0):
                KeyValue = KeyValue + 4;
                break;
            case (0Xd0):
                KeyValue = KeyValue + 8;
                break;
            case (0Xe0):
                KeyValue = KeyValue + 12;
                break;
            }
            while (P1 != 0xf0); // 等待弹起
            Delay10ms(); // 释放消抖
        }
    }
}

void main(void) {

    LCD_Init();
    while (1) {
        matrix_button_down();
        LCD_ShowNum(2, 1, KeyValue, 2);
    }
}