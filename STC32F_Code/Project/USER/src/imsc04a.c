#include "headfile.h"

#define DATA_PIN P10

#define READ_TIMES 10 // 定读取次数,读这么多次,然后取平均值

void IMSC04A_Init(void)
{
    adc_init(ADC_P10, ADC_SYSclk_DIV_2);
}

uint16 IMSC04A_ADC_Read(void)
{
    return adc_once(ADC_P10, ADC_12BIT); 
}

// 计算平均值
uint16 ADC_Press_Average_Data(void)
{
    uint16 temp_val = 0;
    uint8 t;
    for (t = 0; t < READ_TIMES; t++)
    {
        temp_val += IMSC04A_ADC_Read(); // 读取ADC值
        //delay_ms(5);
    }
    temp_val /= READ_TIMES; // 得到平均值
    return (uint16)temp_val;     // 返回算出的ADC平均值
}

// 读取MQ7传感器的电压值
float Press_Get_Vol(void)
{
    uint16 adc_value = 0; // 这是从MQ-7传感器模块电压输出的ADC转换中获得的原始数字值，该值的范围为0到4095，将模拟电压表示为数字值
    float voltage = 0;    // MQ-7传感器模块的电压输出，与一氧化碳的浓度成正比

    adc_value = ADC_Press_Average_Data(); 
    //delay_ms(5);

    voltage = (3.3 / 4096.0) * (adc_value);

    return voltage;
}