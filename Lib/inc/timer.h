#ifndef __TIMER_H__
#define __TIMER_H__
#include "tim.h"

class TIMER : TIM
{
private:
    
public:
    TIMER();
    TIMER(TIM_TypeDef* TIMx,uint16_t ms,void (*event_handler)(),uint8_t Priority);
    ~TIMER();
    void stop();
    void start();
};



#endif
