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
    PWM pwm1(TIM3,TIM_CHANNEL_2,100);
    pwm1.open(50,TIM_CHANNEL_2);
	pwm1.set_Remap(TIM3_REMAP_FULL);
	LED1 = 1;
    sys.delay_ms(200);

    while(1){

    }
    
}
