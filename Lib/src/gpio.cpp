#include "gpio.h"
#include "stm32f10x.h"


void GPIO::Init_Pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode)
{
	RCC->APB2ENR |= 1<<(((uint32_t)GPIOx-(uint32_t)GPIOA)/1024+2);//使能GPIOx的时钟
	
	*(uint32_t *)((uint32_t)GPIOx+((pin>7)?4:0)) &= ~(0X0000000F<<(4*((pin<8)?pin:pin-8)));//清零pin口的配置位
	
	if(mode==GPIO_MODE_INPUT_UP)
	{
		*(uint32_t *)((uint32_t)GPIOx+((pin>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((pin<8)?pin:pin-8));
		GPIOx->ODR |= 1<<pin;
	}
	else if(mode==GPIO_MODE_INPUT_DOWN)
	{
		*(uint32_t *)((uint32_t)GPIOx+((pin>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((pin<8)?pin:pin-8));
		GPIOx->ODR &= ~(1<<pin);
	}
	else
		*(uint32_t *)((uint32_t)GPIOx+((pin>7)?4:0)) |=  (0X0000000F&mode)<<(4*((pin<8)?pin:pin-8));
	    
}


void GPIO::Init(GPIO_TypeDef* GPIOn,GPIO_InitTypeDef* Init_struct)
{
    uint8_t Pins;
    uint8_t t=0;
    Pins = Init_struct->Pin;

    
	for(t=0;t<16;t++)
	{
		if(Pins&0x01) GPIO::Init_Pin(GPIOn,t,Init_struct->Mode);
		Pins>>=1;
	}

    

}


GPIO::GPIO(GPIO_TypeDef* GPIOX,uint16_t Pin,unsigned char mode)
{

	uint16_t Pins = Pin;
	uint8_t i;
    this->GPIOn = GPIOX;
	this->Pin = Pin;
    RCC->APB2ENR |= 1<<(((uint32_t)GPIOX-(uint32_t)GPIOA)/1024+2);//使能GPIOx的时钟
    
	for( i = 0; i < 16; i++)
	{
		if(Pins&0x01)
		{
			*(uint32_t *)((unsigned int)(this->GPIOn)+((i>7)?4:0)) &= ~(0X0000000F<<(4*((i<8)?i:i-8)));//清零Pin口的配置位
			
			if(mode==GPIO_MODE_INPUT_UP)
			{
				*(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((i<8)?i:i-8));
				this->GPIOn->ODR |= 1<<i;
			}
			else if(mode==GPIO_MODE_INPUT_DOWN)
			{
				*(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((i<8)?i:i-8));
				this->GPIOn->ODR &= ~(1<<i);
			}
			else *(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&mode)<<(4*((i<8)?i:i-8));
		}
		Pins>>=1;
		
	}
	
}

GPIO::GPIO(GPIO_TypeDef* GPIOX,uint16_t Pin)
{
	this->GPIOn = GPIOX;
	this->Pin = Pin;
	RCC->APB2ENR |= 1<<(((uint32_t)GPIOX-(uint32_t)GPIOA)/1024+2);//使能GPIOx的时钟
}


GPIO::~GPIO()
{
}

void GPIO::set(int state)
{
	if(state)
	{
		this->GPIOn->ODR |= this->Pin;
	}else
	{
		this->GPIOn->ODR &= (~this->Pin);
	}
	
}

void GPIO::toggle()
{
	uint32_t tmp = this->GPIOn->ODR&this->Pin;
	tmp = ~tmp;
	tmp = tmp&this->Pin;
	this->GPIOn->ODR &= (~this->Pin);
	this->GPIOn->ODR |= tmp;
}

uint16_t GPIO::read()
{
	uint8_t i;
	uint8_t tmp;
	uint16_t Pins = this->Pin;
	for( i = 0; i < 16; i++)
	{
		if(Pins&0x01)
		{
			tmp++;
		}
		Pins>>=1;
	}
	if(tmp==1)
	{
		if(this->GPIOn->IDR&this->Pin)
		{
			return 1;

		}else
		{
			return 0;
		}
		
	}else
	{
		return this->GPIOn->IDR & this->Pin;
	}
	
	
}

uint16_t GPIO::read(GPIO_TypeDef* GPIOn,uint16_t Pin)
{
	uint8_t i;
	uint8_t tmp;
	uint16_t Pins = Pin;
	for( i = 0; i < 16; i++)
	{
		if(Pins&0x01)
		{
			tmp++;
		}
		Pins>>=1;
	}
	if(tmp==1)
	{
		if(GPIOn->IDR&Pin)
		{
			return 1;

		}else
		{
			return 0;
		}
		
	}else
	{
		return GPIOn->IDR & Pin;
	}
}

void GPIO::set(GPIO_TypeDef* GPIOn,uint16_t Pin, int state)
{
	if(state)
	{
		GPIOn->ODR |= Pin;
	}else
	{
		GPIOn->ODR &= (~Pin);
	}
}

void GPIO::setmode(unsigned char mode)
{
	uint16_t Pins = this->Pin;
	uint8_t i;

	for( i = 0; i < 16; i++)
	{
		if(Pins&0x01)
		{
			*(uint32_t *)((unsigned int)(this->GPIOn)+((i>7)?4:0)) &= ~(0X0000000F<<(4*((i<8)?i:i-8)));//清零Pin口的配置位
			
			if(mode==GPIO_MODE_INPUT_UP)
			{
				*(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((i<8)?i:i-8));
				this->GPIOn->ODR |= 1<<i;
			}
			else if(mode==GPIO_MODE_INPUT_DOWN)
			{
				*(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((i<8)?i:i-8));
				this->GPIOn->ODR &= ~(1<<i);
			}
			else *(uint32_t *)((unsigned int)this->GPIOn+((i>7)?4:0)) |=  (0X0000000F&mode)<<(4*((i<8)?i:i-8));
		}
		Pins>>=1;
		
	}	
}

void GPIO::operator = (const uint16_t state)
{
	this->set(state);

}

uint16_t GPIO::operator=(const GPIO &P)
{
	return this->read(this->GPIOn,this->Pin);

}
