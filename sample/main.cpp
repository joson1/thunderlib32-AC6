#include "gpio.h"
#include "sys.h"
#include "usart.h"

int main()
{
	int a;
    sys.Clock_Init();
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