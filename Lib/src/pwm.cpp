#include "pwm.h"
#include "tim.h"
 
PWM::PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq)
{
    uint8_t chs = channel;
    this->TIMn = TIMx;
    this->channel = channel;

	RCC->APB1ENR |= 1<<(((uint32_t)TIMx-(uint32_t)TIM2)/0X0400);    //使能TIMx的时钟
	TIMx->PSC = 23;     								  //定时器计数频率默认3M  HZ
	TIMx->ARR = 3000000/Freq -1;						  //100~60000
	TIMx->CR1 &= 0XFFEF;								  //向上计数

	for( uint8_t i = 0; i < 4; i++)
	{
		if(chs&0x01)
		{
            init_channel(chs);
		}
		chs>>=1;
		
	}
    TIMx->CR1 |= 0X01;							//开启定时器

}
PWM::PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq,uint16_t Remap)
{
    uint8_t chs = channel;
    this->TIMn = TIMx;
    this->channel = channel;

	RCC->APB1ENR |= 1<<(((uint32_t)TIMx-(uint32_t)TIM2)/0X0400);    //使能TIMx的时钟
	TIMx->PSC = 23;     								  //定时器计数频率默认3M  HZ
	TIMx->ARR = 3000000/Freq -1;						  //100~60000
	TIMx->CR1 &= 0XFFEF;								  //向上计数

	for( uint8_t i = 0; i < 16; i++)
	{
		if(chs&0x01)
		{
            init_channel(chs);
		}
		chs>>=1;
		
	}
    TIMx->CR1 |= 0X01;							//开启定时器    
    set_Remap(Remap);
}
PWM::~PWM()
{
    
}

void PWM::set_duty(float percentage,uint8_t channel)
{
	uint16_t ARR = this->TIMn->ARR +1;
	uint16_t CCRx;
	
	percentage = (float)percentage/100;
	CCRx = (float)ARR*percentage;
	for(uint8_t i=0;i<4;++i)
    {
        if(channel&0x01)
        {
            *((uint32_t *)(((uint32_t)this->TIMn+0X34)+(i)*4)) = CCRx;
        }
        channel>>=1;
    }
	
}

void PWM::set_duty(TIM_TypeDef* TIMx,float percentage,uint8_t channel)
{
	uint16_t ARR = TIMx->ARR +1;
	uint16_t CCRx;
	
	percentage = (float)percentage/100;
	CCRx = (float)ARR*percentage;
	for(uint8_t i=0;i<4;++i)
    {
        if(channel&0x01)
        {
            *((uint32_t *)(((uint32_t)TIMx+0X34)+(i)*4)) = CCRx;
        }
        channel>>=1;
    }
}

void PWM::open(float percentage,uint8_t channel)
{
    set_duty(percentage,channel);
    for(uint8_t i = 0; i < 4; ++i)
    {
        if(channel&0x01)
        {
     	this->TIMn->CCER &= (1<<(4*(i)));   
        }
        channel>>=1;
    }

}
void PWM::open(TIM_TypeDef* TIMx,float percentage,uint8_t channel)
{
    set_duty(TIMx,percentage,channel);
    for(uint8_t i = 0; i < 4; ++i)
    {
        if(channel&0x01)
        {
     	TIMx->CCER &= (1<<(4*(i)));   
        }
        channel>>=1;
    }	
}
void PWM::close(uint8_t channel)
{
    for(uint8_t i = 0; i < 4; ++i)
    {
        if(channel&0x01)
        {
     	this->TIMn->CCER &= ~(1<<(4*(i)));   
        }
        channel>>=1;
    } 
}
void PWM::close(TIM_TypeDef* TIMx,uint8_t channel)
{
    for(uint8_t i = 0; i < 4; ++i)
    {
        if(channel&0x01)
        {
     	TIMx->CCER &= ~(1<<(4*(i)));   
        }
        channel>>=1;
    } 
}

void PWM::init_channel(uint8_t ch)
{
	if(ch==1||ch==2)
	{
		ch-=1;
		this->TIMn->CCMR1 &= 0XFF00>>(ch*8);
		this->TIMn->CCMR1 |= 0X0060<<(ch*8);
	}
	else if(ch==3||ch==4)
	{
		ch-=3;
		this->TIMn->CCMR2 &= 0XFF00>>(ch*8);
		this->TIMn->CCMR2 |= 0X0060<<(ch*8);
	}    
}

void PWM::init_channel(TIM_TypeDef* TIMx,uint8_t ch)
{
	if(ch==1||ch==2)
	{
		ch-=1; 
		TIMx->CCMR1 &= 0XFF00>>(ch*8);
		TIMx->CCMR1 |= 0X0060<<(ch*8);
	}
	else if(ch==3||ch==4)
	{
		ch-=3;
		TIMx->CCMR2 &= 0XFF00>>(ch*8);
		TIMx->CCMR2 |= 0X0060<<(ch*8);
	}    
}

void PWM::Init(TIM_TypeDef* TIMx,PWM_InitTypeDef* init_struct)
{
    uint8_t chs = init_struct->channel;


	RCC->APB1ENR |= 1<<(((uint32_t)TIMx-(uint32_t)TIM2)/0X0400);    //使能TIMx的时钟
	TIMx->PSC = 23;     								  //定时器计数频率默认3M  HZ
	TIMx->ARR = 3000000/init_struct->Freq -1;						  //100~60000
	TIMx->CR1 &= 0XFFEF;								  //向上计数

	for( uint8_t i = 0; i < 16; i++)
	{
		if(chs&0x01)
		{
            init_channel(TIMx,chs);
		}
		chs>>=1;
		
	}
    TIMx->CR1 |= 0X01;							//开启定时器    
    set_Remap(TIMx,init_struct->Remap);
}
