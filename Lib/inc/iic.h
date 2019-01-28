#ifndef __IIC_H__
#define __IIC_H__

#include "gpio.h"

class IIC : public GPIO
{
private:
    GPIO SCL;
    GPIO SDA;
public:
    IIC(GPIO SCL,GPIO SDA);
    ~IIC();
};



#endif