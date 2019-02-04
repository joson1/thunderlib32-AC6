#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"


extern void (*TIM2_Irq)();
extern void (*TIM3_Irq)();
extern void (*TIM4_Irq)();
extern void (*TIM5_Irq)();

class TIM
{
protected:
    TIM_TypeDef* TIMn;
public:
    TIM();
    TIM(TIM_TypeDef* TIMn);
    ~TIM();
};





#endif
