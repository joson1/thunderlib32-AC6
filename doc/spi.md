# SPI

## 使用示例

```c++
#include "gpio.h"
#include "sys.h"
#include "spi.h"

GPIO LED1(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP);
int main()
{
    GPIO CS(GPIOB,GPIO_PIN_12,GPIO_MODE_OUTPUT_PP);
    LED1 = 0;
    sys.delay_ms(200);
    spi2.init(SPI_MODE_2,SPI_DATAWIDTH_8);
    spi2.open(1);
    while (1)
    {
        CS = 0;
        spi2.transfer(0xff);
        CS=1;
        sys.delay_ms(500);
    }
}

```