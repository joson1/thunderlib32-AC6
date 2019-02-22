#include "spi.h"
#include "gpio.h"

void _spi1::init(uint8_t SPI_MODE,uint8_t data_width)
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pin = GPIO_PIN_12;
    GPIO::Init(GPIOB,&gpio_init);
    gpio_init.Mode = GPIO_MODE_OUTPUT_FF;
    gpio_init.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_13;
    GPIO::Init(GPIOB,&gpio_init);

    GPIO::set(GPIOB,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14,1);

    RCC->APB2ENR |= 1<<12;

	SPI1->CR1 = 0X0304;
	SPI1->CR1 |= (data_width/8 -1)<<11;
	SPI1->CR1 |= SPI_MODE;
	SPI1->CR1 |= 1<<6;    
    transfer(0XFF);

}

void _spi1::open(uint8_t Speed)
{
	SPI1->CR1 &= 0XFFC7;
	SPI1->CR1 |= (Speed-1)<<3;
	SPI1->CR1 |= 1<<6;    
}

void _spi1::close()
{
    SPI1->CR1 &= ~(1<<6);
}

uint8_t _spi1::transfer(uint8_t data)
{
	u16 val=0;
	while(!(SPI1->SR&0x02))    //等待上一次发送完成
	{
		val++;
		if(val>=0XFFFE)
			return 0;//超时异常
	}
	SPI1->DR = data;
	val = 0;
	while(!(SPI1->SR&0x01))    //等待接收完成
	{
		val++;
		if(val>=0XFFFE)
			return 0;//超时异常
	}
	
	return SPI1->DR;
}




void _spi2::init(uint8_t SPI_MODE,uint8_t data_width)
{
    GPIO_InitTypeDef gpio_init;

    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pin = GPIO_PIN_12;
    GPIO::Init(GPIOB,&gpio_init);
    gpio_init.Mode = GPIO_MODE_OUTPUT_FF;
    gpio_init.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_13;
    GPIO::Init(GPIOB,&gpio_init);

    GPIO::set(GPIOB,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14,1);

    RCC->APB2ENR |= 1<<12;

	SPI1->CR1 = 0X0304;
	SPI1->CR1 |= (data_width/8 -1)<<11;
	SPI1->CR1 |= SPI_MODE;
	SPI1->CR1 |= 1<<6;    
    transfer(0XFF);

}

void _spi2::open(uint8_t Speed)
{
	SPI2->CR1 &= 0XFFC7;
	SPI2->CR1 |= (Speed-1)<<3;
	SPI2->CR1 |= 1<<6;    
}

void _spi2::close()
{
    SPI2->CR1 &= ~(1<<6);
}

uint8_t _spi2::transfer(uint8_t data)
{
	u16 val=0;
	while(!(SPI2->SR&0x02))    //等待上一次发送完成
	{
		val++;
		if(val>=0XFFFE)
			return 0;//超时异常
	}
	SPI2->DR = data;
	val = 0;
	while(!(SPI2->SR&0x01))    //等待接收完成
	{
		val++;
		if(val>=0XFFFE)
			return 0;//超时异常
	}
	
	return SPI2->DR;
}
