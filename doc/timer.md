# 定时器 TIMER

## 使用方法

包含 timer.h  实例化TIMER类使用。注意只能使用通用定时器 TIM2 - TIM5


## 示例

```c++

#include "gpio.h"
#include "timer.h"

void timerhandler();
GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
int main()
{
	int a;
    TIMER timer1(TIM2,500,timerhandler,3);
	LED1 = 0;
    sys.delay_ms(200);
	timer1.start();
    while(1)
    {

    }
    
}

void timerhandler()
{

    LED1.toggle();
}

```

## 函数说明

### 实例化TIMER

```c++
TIMER::TIMER(TIM_TypeDef *TIMx, uint16_t ms, void (*event_handler)(), uint8_t Priority)

```
TIMx: TIM2-TIM5


ms: 定时器时间 单位毫秒


event_handler: 中断处理函数


Priority 优先级0-F(16进制)




### 启动定时器

```c++

void TIMER::start()

```

### 停止定时器

```c++

void TIMER::stop()

```