# ThubnderLib3

thunderLib3是使用C++语言为STM32系列单片机编写的库，库底层直接操作寄存器，相比官方库依赖文件少，易于配置工程，但失去了灵活性，比如不能够很方便的设置GPIO速度，默认配置了最大速度。如果你追求功耗的灵活调控，不建议使用这个库。



## 支持列表
stm32f103


## 使用示例
```c++
#include "gpio.h"
#include "sys.h"


int main()
{

    GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
    LED1.set(0);
    sys.delay_ms(200);
    while(1){
		LED1.toggle();
		sys.delay_ms(500);
        
    }
    
}
```

## [文档](/doc)