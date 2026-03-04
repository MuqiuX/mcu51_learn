/**
 * CPU: 89C52
 * Freq: 12MHz
 * 
 * 本次实现数码管的驱动
 * 这一段实现段选的很巧妙
 *  which = (unsigned char)--which;
 *  P2 &= 0xE3;
 *  P2 |= ~(which << 2);
 * 
 * 数码管驱动:
 *  1. 单片机直接扫描， 3 + 8 （耗费大量cpu运算）
 *  2. 74hc595驱动，两根电源三根数据线 2 + 3
 *  3. 专用驱动 TM1640
 */

#include "config.h"
#include "utils.h"

unsigned char number_hex_list[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void Delay1ms(void) {
    unsigned char data i, j;

    i = 12;
    j = 169;
    do {
        while (--j)
            ;
    } while (--i);
}

// 显示单个数字
void digital_tube_show(int which, int number) {
    // 减一将二进制对齐三位
    // 将三位段选位清零， 保护P0其他位数
    // which对应位数赋值给P2
    which = (unsigned char)--which;
    P2 &= 0xE3;
    P2 |= ~(which << 2);

    P0 = number_hex_list[number];

    // 延时一毫秒防止清除过快体感变暗
    // 清零消除残影
    // 如果需要稳定显示一个数字去掉下面的代码
    Delay1ms();
    P0 = 0;
}

void main(void) {

    while (1) {
        // 段选 位选 段选 位选 段选 位选
        // 上一个位选结束前，下一个段选已经触发， 会产生残影
        digital_tube_show(1, 1);
        digital_tube_show(2, 2);
        digital_tube_show(3, 3);
    }
}