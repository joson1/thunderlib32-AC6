#ifndef __TIM_H__
#define __TIM_H__
#include "stm32f10x.h"

class tim
{
private:
    
public:
    tim(TIM_TypeDef* TIMn);
    ~tim();
};

tim::tim()
{
}

tim::~tim()
{
}



#endif