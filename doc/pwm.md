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

### 初始化PWM

