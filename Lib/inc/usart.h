#ifndef __USART_H__
#define __USART_H__

#include "stdint.h"
#include "stdio.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

extern uint8_t USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern uint16_t USART_RX_STA;         		//接收状态标记	

static class _usart1
{
private:
    
public:
    void begin(uint32_t bound);
    void begin(uint32_t pclk2,uint32_t bound);
    void println(unsigned char* p);
    inline void sendChar(char p);
} usart1;

#endif
