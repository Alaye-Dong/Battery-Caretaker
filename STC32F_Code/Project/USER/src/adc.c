#include "headfile.h"

#define FOSC 52000000UL
#define BRT (65536 - (F0SC / 115200 + 2) / 4)
// 加2操作是为了让Kil编译器//自动实现四舍五入运算
#define VREFH_ADDR CHIPID7
#define VREFL_ADDR CHIPID8

int BGV;

void ADCInit()
{
    EAXFR = 1;
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;

    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    BGV = (VREFH_ADDR << 8) + VREFL_ADDR;

    ADCTIM = 0x3f; // 设置ADC内部时序
    ADCCFG = 0x2f;
    // 设置ADC时钟为系统时钟2 / 16
    ADC_CONTR = 0x8f;
    // 使能ADC模块并选择第15通道子
}

int ADCRead()
{
    int res;
    ADC_START = 1;
    _nop_();
    _nop_();
    while (!ADC_FLAG);
    ADC_FLAG = 0;
    res = (ADC_RES << 8) | ADC_RESL;
    return res;
}

int ADC_Main(void)
{
    int res;
    int vcc;
    int i;

    ES = 1;
    EA = 1;

    res = 0;
    for (i = 0; i < 8; i++)
    {
        res += ADCRead();
    }

    res >>= 3;
    vcc = (int)(4096L * BGV / res);
    return vcc;
}