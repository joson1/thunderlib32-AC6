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
    this->TIMn = TIMx;
    RCC->APB1ENR |= 1 << ((TIMx - TIM2) / 0X0400); //使能TIMx的时钟
    TIMx->PSC = (7200 - 1);                        //时钟分频系数,定时器计数时钟
    TIMx->CR1 |= (0) << 4;                         //计数模式，向上
    TIMx->ARR = (ms * 10) - 1;                     //溢出周期
    if (TIMx == TIM2)
    {
        n = 28;
        TIM2_Irq = event_handler;
    }

    else if (TIMx == TIM3)
    {
        n = 29;
        TIM3_Irq = event_handler;
    }

    else if (TIMx == TIM4)
    {
        n = 30;
        TIM4_Irq = event_handler;
    }

    else
    {
        n = 50;
        TIM5_Irq = event_handler;
    }
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

