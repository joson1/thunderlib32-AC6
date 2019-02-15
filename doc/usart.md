# USART 串口


## 使用方法

包含 usart.h


调用 usart1.begin(115200) 使用串口1 波特率设置为 115022

可使用 printf() usart1.println()   和 scanf() 进行串口通讯


> 注意 printf() 和 scanf() 调用的是 usart1


## 示例
```c++
#include "gpio.h"
#include "sys.h"
#include "usart.h"

int main()
{
	int a;
	usart1.begin(115200);
    GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
    sys.delay_ms(200);
	printf("ss");
	scanf("%d",&a);
    while(1){
		
		LED1.toggle();
		sys.delay_ms(500);
        
    }
    
}


```