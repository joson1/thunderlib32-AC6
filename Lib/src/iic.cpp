#include "iic.h"

IIC::IIC(GPIO SCL,GPIO SDA)
{
    this->SCL = SCL;
    this->SDA = SDA;
    this->SCL.setmode(GPIO_MODE_OUTPUT_PP);
    this->SDA.setmode(GPIO_MODE_OUTPUT_PP);

}

IIC::~IIC()
{
}

