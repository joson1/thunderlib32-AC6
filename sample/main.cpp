#include "gpio.h"
#include "sys.h"
#include "usart.h"
#include "iic.h"
#include "timer.h"


void timerhandler();
GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
int main()
{
	int a;
    TIMER timer1(TIM4,500,timerhandler,3);
	//usart1.begin(115200);

	LED1 = 0;
    sys.delay_ms(200);
	timer1.start();
    while(1){
		
//		LED1.toggle();
//		sys.delay_ms(500);
//        
    }
    
}

void timerhandler()
{
   // GPIO::toggle(GPIOC,GPIO_PIN_13);
    LED1.toggle();
}
