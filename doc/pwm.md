# PWM 脉宽调制输出

## 使用示例

```c++

#include "pwm.h"
#include "sys.h"

int main()
{
    PWM pwm1(TIM2,TIM_CHANNEL_1,100);
    pwm1.open(50,TIM_CHANNEL_1);

    sys.delay_ms(200);

    while(1)
    {

    }
    
}


```
## 函数说明
### TIM的通道
```c++
#define TIM_CHANNEL_1 0x01
#define TIM_CHANNEL_2 0x02
#define TIM_CHANNEL_3 0X04
#define TIM_CHANNEL_4 0X08
#define TIM_CHANNEL_ALL 0x0f

```
### TIM的重映射
```c++

#define TIM1_REMAP_NONE 00
#define TIM1_REMAP_PARTIAL 1
#define TIM1_REMAP_FULL 3

#define TIM2_REMAP_NONE 0
#define TIM2_REMAP_PARTIAL_1 1
#define TIM2_REMAP_PARTIAL_2 2
#define TIM2_REMAP_FULL 3

#define TIM3_REMAP_NONE 00
#define TIM3_REMAP_PARTIAL 2
#define TIM3_REMAP_FULL 3

#define TIM4_REMAP_NONE 00
#define TIM4_REMAP_ALL 1

#define TIM5_CH4_REMAP_PA3 0
#define TIM5_CH4_REMAP_LSI 1

```

### 初始化PWM


初始并实例化一个pwm

- Freq PWM频率 单位Hz


PWM::PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq)
```c++
PWM pwm1(TIM2,TIM_CHANNEL_1,100);
```

初始并实例化一个pwm,并且制定重映射

PWM::PWM(TIM_TypeDef* TIMx,uint8_t channel,uint16_t Freq,uint16_t Remap)

```c++
PWM pwm1(TTM2,TIM_CHANNEL_1,100,TIM2_REMAP_PARTIAL_1);
```


只初始化但不实例化

void PWM::Init(TIM_TypeDef* TIMx,PWM_InitTypeDef* init_struct)

```c++
PWM_InitTypeDef PwmInit;
PwmInit.channel = TIM_CHANNEL_1;
PwmInit.Freq = 100;
PwmInit.Remap = TIM2_REMAP_PARTIAL_1;

PWM::Init(TIM2,&PwmInit);

```
> 可以使用“|”来同时操作多个通道，例如
> PWM pwm1(TIM2,TIM_CHANNEL_1|TIM_CHANNEL_2,100);


### 开启一个PWM

已经实例化的
- percentage 占空比 0-100

void PWM::open(float percentage,uint8_t channel)
```c++
pwm1.open(50,TIM_CHANNEL_1);
```

未示例化的（但必须执行过初始化）


PWM::open(TIM_TypeDef* TIMx,float percentage,uint8_t channel)


```c++

PWM::open(TTM2,50,TIM_CHANNEL_1);

```

### 改变占空比


已经实例化的


void PWM::set_duty(float percentage,uint8_t channel)

```C++
pwm1.set_duty(30,TIM_CHANNEL_1);
```

未示例化的（但必须执行过初始化）


void PWM::set_duty(TIM_TypeDef* TIMx,float percentage,uint8_t channel)
```c++
pwm1.set_duty(TTM2,30,TIM_CHANNEL_1);
```
### 关闭PWM


已经实例化的


void PWM::close(uint8_t channel)

```c++
pwm1.close(TIM_CHANNEL_1);
```