#include "timer.h"
#include "sys.h"

/*
TIM2-TIM5|
定时器时间 单位毫秒|
中断处理函数|
优先级0-F
*/
TIMER::TIMER(TIM_TypeDef *TIMx, uint16_t ms, void (*event_handler)(), uint8_t Priority)
{
    uint8_t n;
    uint32_t tmp;
    this->TIMn = TIMx;
    tmp = ((uint32_t)TIMx - (uint32_t)0x40000000) >>10;
    RCC->APB1ENR |= 1 <<tmp; //使能TIMx的时钟
    TIMx->PSC = (7200 - 1);                        //时钟分频系数,定时器计数时钟
    TIMx->CR1 |= (0) << 4;                         //计数模式，向上
    TIMx->ARR = (ms * 10) - 1;                     //溢出周期
    if (TIMx == TIM2)
    {
        n = TIM2_IRQn;
        TIM2_update_Irq = event_handler;
    }

    else if (TIMx == TIM3)
    {
        n = TIM3_IRQn;
        TIM3_update_Irq = event_handler;
    }
    
    else if (TIMx == TIM4)
    {
        n = TIM4_IRQn;
        TIM4_update_Irq = event_handler;
    }
#ifdef STM32F10X_HD
    else if(TIMx == TIM5)
    {
        n = TIM5_IRQn;
        TIM5_update_Irq = event_handler;
    }

    else if(TIMx == TIM6)
    {
        n = TIM6_IRQn;
        TIM6_update_Irq = event_handler;
    }
    else if(TIMx == TIM7)
    {
        n = TIM7_IRQn;
        TIM7_update_Irq = event_handler;
    }
 #endif
    TIMx->CNT = 1;
    NVIC->IP[n] = (Priority << 4);       //中断优先级设置
    NVIC->ISER[n / 32] |= 1 << (n % 32); //中断通道使能
    TIMx->DIER |= 0X0001;                //开启定时器更新中断
    TIMx->SR &= 0xfe;
}
TIMER::TIMER()
{
}

TIMER::~TIMER()
{
    this->stop();
}

void TIMER::stop()
{
    this->TIMn->CR1 &= ~0x01;
}
void TIMER::start()
{
    this->TIMn->CR1 |= 0x01;
}

