#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"


extern void (*TIM2_update_Irq)();
extern void (*TIM3_update_Irq)();
extern void (*TIM4_update_Irq)();
extern void (*TIM5_update_Irq)();
extern void (*TIM6_update_Irq)();
extern void (*TIM7_update_Irq)();

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
