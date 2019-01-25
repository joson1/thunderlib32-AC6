# GPIO使用方法

## 使用C++语法

```c++
#include "gpio.h"
#include "sys.h"


int main()
{
    sys.Clock_Init();
    GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
    LED1.set(0);
    sys.delay_ms(200);
    while(1){
		LED1.toggle();
		sys.delay_ms(500);
        
    }
    
}
```
### API参考

#### 指定初始化的引脚
```css
GPIO_PIN_0  
GPIO_PIN_1  
GPIO_PIN_2  
GPIO_PIN_3  
GPIO_PIN_4  
GPIO_PIN_5  
GPIO_PIN_6  
GPIO_PIN_7  
GPIO_PIN_8  
GPIO_PIN_9  
GPIO_PIN_10 
GPIO_PIN_11 
GPIO_PIN_12 
GPIO_PIN_13 
GPIO_PIN_14 
GPIO_PIN_15 
GPIO_PIN_All
```


可以使用 GPIO_PIN_11 | GPIO_PIN_15 的方式同时初始化多个引脚

#### GPIO模式有


```CSS
GPIO_MODE_OUTPUT_PP 		0X3     //推挽输出
GPIO_MODE_OUTPUT_FF 		0XB     //复用推挽
GPIO_MODE_INPUT_UP  		0X9     //上拉输入
GPIO_MODE_INPUT_DOWN		0X8     //下拉输入
GPIO_MODE_INPUT_ANALOG      0X0	    //模拟输入

```

#### 读取引脚状态
uint16_t GPIO::read()


返回当前实例对应的引脚状态，需在之前将对应的引脚设置为输入

