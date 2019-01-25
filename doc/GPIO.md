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


uint16_t GPIO::read(GPIO_TypeDef* GPIOn,uint16_t Pin)


返回指定IO口的状态，需在之前将对应的引脚设置为输入
```c++
uint16_t IN1;
uint16_t IN2;
uint16_t IN3;

IN1=GPIO::read(GPIOA,GPIO_PIN_1) //读取GPIOA1的状态

IN2=GPIO::read(GPIOB,GPIO_PIN_1|GPIO_PIN_12) //读取GPIOB1 和 GPIOB12 的状态，存入IN2中 
                                             //IN2的第1位对应读取GPIOB1的真实状态，IN2的第12位对应GPIOB12的真实状态

IN3 = GPIO::read(GPIOB,GPIO_PIN_All)  // 将GPIOB所有的引脚状态读取出来，存入IN3中

```

