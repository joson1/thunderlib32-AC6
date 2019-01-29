#include "iic.h"
#include "sys.h"

IIC::IIC(const GPIO &SCL,const GPIO &SDA)
{
    uint8_t i;
    uint16_t Pins_SCL = SCL.Pin;
    uint16_t Pins_SDA = SDA.Pin; 
    this->SCL = SCL;
    this->SDA = SDA;
    this->SCL.setmode(GPIO_MODE_OUTPUT_PP);
    this->SDA.setmode(GPIO_MODE_OUTPUT_PP);
    for(i = 0; i < 16; i++)
    {
        if(Pins_SCL&0x01)
        {
            SCL_Pin = i;
        }
        Pins_SCL>>=1;
    }
    for(i = 0; i < 16; i++)
    {
        if(Pins_SDA&0x01)
        {
            SDA_Pin = i;
        }
        Pins_SDA >>= 1;
    }
    
}

IIC::~IIC()
{
}

void IIC::SCL_set(uint8_t val)
{
    this->SCL=val; 

}
void IIC::SDA_set(uint8_t val)
{
    this->SDA = val;

}
uint8_t IIC::SDA_read()
{

    return this->SDA.read();
}

void IIC::SDA_IN()
{
    *(uint32_t *)((uint32_t)this->SDA.GPIOn+((SDA_Pin>7)?4:0)) |=  (0X0000000F&0X8)<<(4*((SDA_Pin<8)?SDA_Pin:SDA_Pin-8));
    this->SDA.GPIOn->ODR |= 1<<SDA_Pin;    
}
void IIC::SDA_OUT()
{
    *(uint32_t *)((uint32_t)this->SDA.GPIOn+((SDA_Pin>7)?4:0)) |=  (0X0000000F&GPIO_MODE_OUTPUT_PP)<<(4*((SDA_Pin<8)?SDA_Pin:SDA_Pin-8));
}

void IIC::start()
{
    SDA_OUT();
    SCL_set(1);
    SDA_set(1);
    sys.delay_us(4);
    SDA_set(0);
    sys.delay_us(4);
    SCL_set(0);
}
void IIC::stop()
{
    SDA_OUT();
    SCL_set(0);
    SDA_set(0);
    sys.delay_us(4);
    SCL_set(1);
    SDA_set(1);
    sys.delay_us(4);

}
void IIC::write(uint8_t val)
{
	uint8_t mx;
	SDA_OUT();
	SCL_set(0);
	for(mx=0x80;mx!=0;mx>>=1)
	{
		if(mx&val)
			SDA_set(1);
		else
			SDA_set(0);
		sys.delay_us(2);
		SCL_set(1);
		sys.delay_us(2);
		SCL_set(0);
	}    

}
/*ack:是否回应ack    0：不回应  1：回应*/
uint8_t IIC::read(uint8_t ack)
{
	uint8_t mx,dat;
	SDA_IN();
	for(mx=0x80;mx!=0;mx>>=1)
	{
		SCL_set(0);
		sys.delay_us(2);
		SCL_set(1);
		if(SDA_read())
			dat |= mx;
		else
			dat &= ~mx;
		sys.delay_us(1);
	}
	//ack
	SDA_OUT();
	SCL_set(0);
	SDA_set(!ack);
	sys.delay_us(2);
	SDA_set(1);
	sys.delay_us(2);
	SDA_set(0);
	
	return dat;
}
uint8_t IIC::wait_ack()
{
	uint8_t time=0;
	SDA_IN();
	SCL_set(1);
	sys.delay_us(2);
	while(SDA_read())
	{
		time++;
		if(time>250)
		{
            
			stop();
			return 0;
		}
	}
	SCL_set(0);
	return 1;
}
