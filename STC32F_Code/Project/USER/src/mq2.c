#include "headfile.h"

#define CAL_PPM 10 // 校准环境中PPM值
#define RL 10      // RL阻值
#define R0 26      // R0阻值

#define SMOG_READ_TIMES 10 // 定义烟雾传感器读取次数,读这么多次,然后取平均值

void MQ2_Init(void)
{
    adc_init(ADC_P13, ADC_SYSclk_DIV_2);
}

uint16 MQ2_ADC_Read(void)
{
    return adc_once(ADC_P13, ADC_12BIT); 
}

// 计算平均值
uint16 ADC_Average_Data()
{
    uint16 temp_val = 0;
    uint8 t;
    for (t = 0; t < SMOG_READ_TIMES; t++)
    {
        temp_val += MQ2_ADC_Read(); // 读取ADC值
        //delay_ms(5);
    }
    temp_val /= SMOG_READ_TIMES; // 得到平均值
    return (uint16)temp_val;     // 返回算出的ADC平均值
}

// 读取MQ7传感器的电压值
float Smog_Get_Vol(void)
{
    uint16 adc_value = 0; // 这是从MQ-7传感器模块电压输出的ADC转换中获得的原始数字值，该值的范围为0到4095，将模拟电压表示为数字值
    float voltage = 0;    // MQ-7传感器模块的电压输出，与一氧化碳的浓度成正比

    adc_value = ADC_Average_Data(); 
    //delay_ms(5);

    voltage = (3.3 / 4096.0) * (adc_value);
    return voltage;
}



// 计算Smog_ppm
float Smog_GetPPM()
{
    float RS = (3.3f - Smog_Get_Vol()) / Smog_Get_Vol() * RL;
    float ppm = 98.322f * pow(RS / R0, -1.458f);
    return ppm;
}

// 传感器校准函数，根据当前环境PPM值与测得的RS电压值，反推出R0值。
// 在空气中运行过后测出R0为26
float MQ7_PPM_Calibration()
{
    float RS_value = 0;
    float R0_value = 0;
    RS_value = (3.3f - Smog_Get_Vol()) / Smog_Get_Vol() * RL;//RL	10  // RL阻值
    R0_value = RS_value / pow(CAL_PPM / 98.322, 1 / -1.458f);//CAL_PPM  10  // 校准环境中PPM值
    return R0_value;
}