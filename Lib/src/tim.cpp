#include "tim.h"
#include "STDDEF.H"

void (*TIM2_update_Irq)() = NULL;
void (*TIM3_update_Irq)() = NULL;
void (*TIM4_update_Irq)() = NULL;
void (*TIM5_update_Irq)() = NULL;
void (*TIM6_update_Irq)() = NULL;
void (*TIM7_update_Irq)() = NULL;


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
        (*TIM2_update_Irq)();
       
    }
    TIM2->SR &= 0XFFFE;
}

void TIM3_IRQHandler()
{
    if(TIM3->SR&0x0001)
    {
        (*TIM3_update_Irq)();
    }

    TIM3->SR &= 0XFFFE;
}

void TIM4_IRQHandler()
{
    if(TIM4->SR & 0x0001)
    {
        (*TIM4_update_Irq)();
    }
    
    TIM4->SR &= 0XFFFE;    
}

void TIM5_IRQHandler()
{
    if(TIM5->SR&0x0001)
    {
        (*TIM5_update_Irq)();
    }
    
    TIM5->SR &= 0XFFFE;        
}
void TIM6_IRQHandler()
{
    if(TIM6->SR & 0x0001)
    {
        (*TIM6_update_Irq)();
    }
    
    TIM6->SR &= 0XFFFE;        
}

void TIM7_IRQHandler()
{
    if(TIM7->SR & 0x0001)
    {
        (*TIM7_update_Irq)();
    }

    TIM7->SR &= 0XFFFE;        
}

}
