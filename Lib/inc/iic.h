#ifndef __IIC_H__
#define __IIC_H__

#include "gpio.h"

class IIC 
{
private:
    GPIO SCL;
    GPIO SDA;
    uint8_t SCL_Pin;
    uint8_t SDA_Pin;
    void SCL_set(uint8_t val);
    void SDA_set(uint8_t val);
    void SDA_IN();
    void SDA_OUT();
    uint8_t SDA_read();
public:
    IIC(const GPIO &SCL,const GPIO &SDA);
    ~IIC();
    void start();
    void stop();
    void write(uint8_t val);
    uint8_t read(uint8_t ack);
    uint8_t wait_ack();
};



#endif
