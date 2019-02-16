#include "gpio.h"
#include "sys.h"
#include "usart.h"
#include "iic.h"
#include "timer.h"
#include "pwm.h"

void timerhandler();
GPIO LED1(GPIOC,GPIO_PIN_13,GPIO_MODE_OUTPUT_PP);
int main()
{
    PWM pwm1(TIM2,TIM_CHANNEL_1,100);
    pwm1.open(50,TIM_CHANNEL_1);
	LED1 = 0;
    sys.delay_ms(200);

    while(1){

    }
    
}
