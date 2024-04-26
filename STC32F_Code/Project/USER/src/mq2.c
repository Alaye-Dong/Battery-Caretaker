#include "headfile.h"

#define CAL_PPM 10 // У׼������PPMֵ
#define RL 10      // RL��ֵ
#define R0 26      // R0��ֵ

#define SMOG_READ_TIMES 10 // ����������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ

void MQ2_Init(void)
{
    adc_init(ADC_P13, ADC_SYSclk_DIV_2);
}

uint16 MQ2_ADC_Read(void)
{
    return adc_once(ADC_P13, ADC_12BIT); 
}

// ����ƽ��ֵ
uint16 ADC1_Average_Data()
{
    uint16 temp_val = 0;
    uint8 t;
    for (t = 0; t < SMOG_READ_TIMES; t++)
    {
        temp_val += MQ2_ADC_Read(); // ��ȡADCֵ
        delay_ms(5);
    }
    temp_val /= SMOG_READ_TIMES; // �õ�ƽ��ֵ
    return (uint16)temp_val;     // ���������ADCƽ��ֵ
}

// ��ȡMQ7�������ĵ�ѹֵ
float Smog_Get_Vol(void)
{
    uint16 adc_value = 0; // ���Ǵ�MQ-7������ģ���ѹ�����ADCת���л�õ�ԭʼ����ֵ����ֵ�ķ�ΧΪ0��4095����ģ���ѹ��ʾΪ����ֵ
    float voltage = 0;    // MQ-7������ģ��ĵ�ѹ�������һ����̼��Ũ�ȳ�����

    adc_value = ADC1_Average_Data(); 
    delay_ms(5);

    voltage = (3.3 / 4096.0) * (adc_value);

    return voltage;
}
/*********************
// ������У׼���������ݵ�ǰ����PPMֵ���õ�RS��ѹֵ�����Ƴ�R0ֵ��
// �ڿ��������й�����R0Ϊ26
float MQ7_PPM_Calibration()
{
    float RS = 0;
    float R0 = 0;
    RS = (3.3f - Smog_Get_Vol()) / Smog_Get_Vol() * RL;//RL	10  // RL��ֵ
    R0 = RS / pow(CAL_PPM / 98.322, 1 / -1.458f);//CAL_PPM  10  // У׼������PPMֵ
    return R0;
}
**********************/

// ����Smog_ppm
float Smog_GetPPM()
{
    float RS = (3.3f - Smog_Get_Vol()) / Smog_Get_Vol() * RL;
    float ppm = 98.322f * pow(RS / R0, -1.458f);
    return ppm;
}