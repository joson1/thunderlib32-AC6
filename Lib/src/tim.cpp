#include "tim.h"
#include "STDDEF.H"

void (*TIM2_Irq)() = NULL;
void (*TIM3_Irq)() = NULL;
void (*TIM4_Irq)() = NULL;
void (*TIM5_Irq)() = NULL;



TIM::TIM(TIM_TypeDef* TIMn)
{

}

TIM::TIM()
{
} 

TIM::~TIM()
{
}
extern "C"{

void TIM2_IRQHandler()
{
    if((TIM2->SR)&0X0001)
    {
        (*TIM2_Irq)();
       
    }
    TIM2->SR &= 0XFFFE;
}

void TIM3_IRQHandler()
{
    (*TIM3_Irq)();
    TIM3->SR &= 0XFFFE;
}

void TIM4_IRQHandler()
{
    (*TIM4_Irq)();
    TIM4->SR &= 0XFFFE;    
}

void TIM5_IRQHandler()
{
    (*TIM5_Irq)();
    TIM5->SR &= 0XFFFE;        
}


}
