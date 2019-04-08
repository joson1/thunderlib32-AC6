#ifndef __SPI_H__
#define __SPI_H__
#include "sys.h"

#define SPI_MODE_1 0X02
#define SPI_MODE_2 0X03
#define SPI_MODE_3 0X01
#define SPI_MODE_4 0X00

#define SPI_DATAWIDTH_8 8
#define SPI_DATAWIDTH_16 16

static class _spi1
{
private:

public:
    void init(uint8_t SPI_MODE,uint8_t data_width);
    void open(uint8_t Speed);
    void close();
    uint16_t transfer(uint16_t data);
} spi1;

static class _spi2
{
private:

public:
    void init(uint8_t SPI_MODE,uint8_t data_width);
    void open(uint8_t Speed);
    void close();
    uint8_t transfer(uint8_t data);
} spi2;



#endif
