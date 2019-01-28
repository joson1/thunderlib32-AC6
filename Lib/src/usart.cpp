#include "usart.h"
#include "sys.h"
#include "stdarg.h"
#include <time.h>
#include <rt_misc.h>


#pragma import(__use_no_semihosting_swi)
struct std::__FILE { int handle; /* Add whatever you need here */ };
	
std::FILE std::__stdin;
std::FILE std::__stdout;
std::FILE std::__stderr;



extern "C"
{

	int sendchar(int ch)
	{
		while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
		USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
		return ch;
	}

	int getkey()
	{
		while(!(USART1->SR&0x20));
		return USART1->DR;
	}

	int fputc(int ch, FILE *f) {
	return (sendchar(ch));
	}

	int fgetc(FILE *f) {
	return (sendchar(getkey()));
	}


	int ferror(FILE *f) {
	/* Your implementation of ferror */
	return EOF;
	}


	void _ttywrch(int ch) {
	sendchar (ch);
	}


	void _sys_exit(int return_code) {
	while (1);    /* endless loop */
	}





}



//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t USART_RX_STA=0;       //接收状态标记	  
  
void USART1_IRQHandler(void)
{
// 	u8 res;	
// #if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
// 	OSIntEnter();    
// #endif
// 	if(USART1->SR&(1<<5))	//接收到数据
// 	{	 
// 		res=USART1->DR; 
// 		if((USART_RX_STA&0x8000)==0)//接收未完成
// 		{
// 			if(USART_RX_STA&0x4000)//接收到了0x0d
// 			{
// 				if(res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
// 				else USART_RX_STA|=0x8000;	//接收完成了 
// 			}else //还没收到0X0D
// 			{	
// 				if(res==0x0d)USART_RX_STA|=0x4000;
// 				else
// 				{
// 					USART_RX_BUF[USART_RX_STA&0X3FFF]=res;
// 					USART_RX_STA++;
// 					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
// 				}		 
// 			}
// 		}  		 									     
// 	}
// #if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
// 	OSIntExit();  											 
// #endif
} 

void _usart1::begin(uint32_t bound)
{
    uint32_t pclk2 = 72;
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置 
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断 
	// USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	// sys.MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
 
}

void _usart1::begin(uint32_t pclk2,uint32_t bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置 
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.

	//使能接收中断 
	// USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	// sys.MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 

}

inline void _usart1::sendChar(char p)
{
	while((USART1->SR&0X40)==0);
	USART1->DR = p;
}

void _usart1::println(unsigned char* p)
{
    while(*p)
	{
		sendChar(*p);
		p++;

    }
	sendChar('\r');
	sendChar('\n');
    
}
