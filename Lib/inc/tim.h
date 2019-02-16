#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"

#define TIM_CHANNEL_1 0x01
#define TIM_CHANNEL_2 0x02
#define TIM_CHANNEL_3 0X04
#define TIM_CHANNEL_4 0X08
#define TIM_CHANNEL_ALL 0x0f

#define TIM1_REMAP_NONE 00
#define TIM1_REMAP_PARTIAL 1
#define TIM1_REMAP_FULL 3

#define TIM2_REMAP_NONE 00
#define TIM2_REMAP_PARTIAL_1 1
#define TIM2_REMAP_PARTIAL_2 2
#define TIM2_REMAP_FULL 3

#define TIM3_REMAP_NONE 00
#define TIM3_REMAP_PARTIAL 2
#define TIM3_REMAP_FULL 3

#define TIM4_REMAP_NONE 00
#define TIM4_REMAP_ALL 1

#define TIM5_CH4_REMAP_PA3 0
#define TIM5_CH4_REMAP_LSI 1

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
    void set_counter_mode(uint8_t mode);
    void set_Remap(uint16_t Remap);
    static void set_Remap(TIM_TypeDef* TIMn, uint16_t Remap);
};





#endif
