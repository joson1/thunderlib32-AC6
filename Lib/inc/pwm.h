#ifndef __PWM_H__
#define __PWM_H__
#include "tim.h"

typedef struct 
{
    uint8_t channel;
    uint16_t Freq;
    uint16_t Remap;
} PWM_InitTypeDef;



class PWM : TIM
{
private:
    uint8_t channel;
    void init_channel(uint8_t ch);
    static void init_channel(TIM_TypeDef* TIMx,uint8_t ch);
public:
    PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq,uint16_t Remap);
    PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq);
    ~PWM();
    static void Init(TIM_TypeDef* TIMx,PWM_InitTypeDef* init_struct);
    void set_duty(float percentage,uint8_t channel);
    static void set_duty(TIM_TypeDef* TIMx,float percentage,uint8_t channel);
    void open(float percentage,uint8_t channel);
    static void open(TIM_TypeDef* TIMx,float percentage,uint8_t channel);
    void close(uint8_t channel);
    static void close(TIM_TypeDef* TIMx,uint8_t channel);



};


#endif
