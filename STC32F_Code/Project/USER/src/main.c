/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2023-07-27

 ********************************************************************************************************************/
#include "headfile.h"

// 关于内核频率的设定，可以查看board.h文件
// 在board_init中,已经将P54引脚设置为复位
// 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可

float the_ppm;
void main()
{
    clock_init(SYSTEM_CLOCK_52M); // 初始化系统频率,勿删除此句代码。
    board_init();                 // 初始化寄存器,勿删除此句代码。

    // 此处编写用户代码 例如外设初始化代码等
    MQ2_Init();
    // ADC初始化
    //  adc_init(ADC_P00,ADC_SYSclk_DIV_2);
    //  adc_init(ADC_P01,ADC_SYSclk_DIV_2);
    //  adc_init(ADC_P05,ADC_SYSclk_DIV_2);
    //  adc_init(ADC_P06,ADC_SYSclk_DIV_2);
    //  adc_init(ADC_P11,ADC_SYSclk_DIV_2);
    //  adc_init(ADC_P13,ADC_SYSclk_DIV_2);    
    BEEP_Init();
    lcd_init();    // 屏幕初始化
    eeprom_init(); // eeprom初始化

    
    
    //pit_timer_ms(TIM_4, 5); // 设置中断定时

    BEEP_ON_ms(100);

    while (1)
    {
        // 此处编写需要循环执行的代码
         Keystroke_Menu();

        // read_dht11(); // 读取DHT11的数值
        // lcd_showint32(14 * 8, 5, CHH, 3);

        // lcd_showstr(1 * 8, 3, "TEST");
        // lcd_showfloat(8 * 8, 0,Smog_Get_Vol() , 4, 3);
    }
}
