# GPIO使用方法

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
## API参考

### 指定初始化的引脚
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

### GPIO模式有


```CSS
GPIO_MODE_OUTPUT_PP 		0X3     //推挽输出
GPIO_MODE_OUTPUT_FF 		0XB     //复用推挽
GPIO_MODE_INPUT_UP  		0X9     //上拉输入
GPIO_MODE_INPUT_DOWN		0X8     //下拉输入
GPIO_MODE_INPUT_ANALOG      0X0	    //模拟输入

```
### GPIO初始化
方式1： 实例化GPIO并初始化GPIO
```c++
GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
```


方式2：仅初始化
```c++
GPIO_InitTypeDef init;
init.Pin = GPIO_PIN_2;
init.Mode = GPIO_MODE_OUTPUT_PP;

GPIO::Init(GPIOC,&init);

```


### 设置引脚状态

#### 直接赋值
```c++
GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
LED1 = 0;

```

#### 调用函数

void GPIO::set(int state)


设置当前实例对应的引脚状态 state为要设置的状态 0 或 1

```c++

  GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
  LED1.set(0);

```


GPIO::set(GPIO_TypeDef* GPIOn,uint16_t Pin, int state)


设置任意IO的引脚状态，需要在之前将其初始化为输出

```c++

GPIO::set(GPIOB,GPIO_PIN_5,0);  //设置GPIOB5为0

GPIO::set(GPIOB,GPIO_PIN_2|GPIO_PIN_7,0);  // 设置GPIOB2和GPIOB7为0

GPIO::set(GPIOE,GPIO_PIN_All,1); //设置GPIOE所有的引脚为1
```


void GPIO::toggle()


翻转当前实例对应IO的电平状态


```c++

  GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
  LED1.toggle();

```

void GPIO::toggle(GPIO_TypeDef* GPIOn,uint16_t Pin);


翻转任意IO的电平状态，需要在之前将其初始化为输出


```c++

GPIO::toggle(GPIOE,GPIO_PIN_1); //翻转GPIOE1的电平状态

```

### 读取引脚状态

#### 直接获取
```c++
GPIO KEY1(GPIOC,GPIO_PIN_13,GPIO_MODE_INPUT_UP);
uint16_t key = KEY1;

```

#### 调用函数
uint16_t GPIO::read()


返回当前实例对应的引脚状态，需在之前将对应的引脚设置为输入
```c++

  GPIO KEY1(GPIOC,GPIO_PIN_13,GPIO_MODE_INPUT_UP);
  bool key = KEY1.read();

```

uint16_t GPIO::read(GPIO_TypeDef* GPIOn,uint16_t Pin)


返回指定IO口的状态，需在之前将对应的引脚设置为输入
```c++
uint16_t IN1;
uint16_t IN2;
uint16_t IN3;

IN1=GPIO::read(GPIOA,GPIO_PIN_1); //读取GPIOA1的状态

IN2=GPIO::read(GPIOB,GPIO_PIN_1|GPIO_PIN_12); //读取GPIOB1 和 GPIOB12 的状态，存入IN2中 
                                             //IN2的第1位对应读取GPIOB1的真实状态，IN2的第12位对应GPIOB12的真实状态

IN3 = GPIO::read(GPIOB,GPIO_PIN_All);  // 将GPIOB所有的引脚状态读取出来，存入IN3中

```

