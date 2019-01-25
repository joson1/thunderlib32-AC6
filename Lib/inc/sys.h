#ifndef __SYS_H
#define __SYS_H	  
#include <stm32f10x.h>   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//系统时钟初始化（适合STM32F10x系列）		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2010/1/1
//版本：V1.9
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.4修改说明
//把NVIC KO了,没有使用任何库文件!
//加入了JTAG_Set函数
//V1.5 20120322
//增加void INTX_DISABLE(void)和void INTX_ENABLE(void)两个函数
//V1.6 20120412
//1,增加MSR_MSP函数												    
//2,修改VECT_TAB_RAM的默认偏移,设置为0.
//V1.7 20120818
//1,添加ucos支持配置宏SYSTEM_SUPPORT_UCOS
//2,修改了注释
//3,去掉了不常用函数BKP_Write
//V1.8 20131120
//1,修改头文件为stm32f10x.h,不再使用stm32f10x_lib.h及其相关头文件
//V1.9 20150109
//1,修改头文件为MY_NVIC_Init函数部分代码以支持向量号大于63的中断的设置
//2,修改WFI_SET/INTX_DISABLE/INTX_ENABLE等函数的实现方式
//V2.0 20150322
//修改SYSTEM_SUPPORT_UCOS为SYSTEM_SUPPORT_OS
////////////////////////////////////////////////////////////////////////////////// 	  

//0,不支持OS
//1,支持OS
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持OS
																	    

//Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //下降沿触发
#define RTIR   2  //上升沿触发
								   

//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	


static class _sys
{

private:
    static uint8_t  fac_us;							//us延时倍乘数			   
    static uint16_t fac_ms;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
        
    static void delay_init(uint8_t SYSCLK);
    static void MYRCC_DeInit(void);
public:
    static void Clock_Init();  //时钟初始化  
    static void Soft_Reset();      //系统软复位
    static void Standby();         //待机模式 	
    static void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
    static void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//设置NVIC分组
    static void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
    static void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//外部中断配置函数(只对GPIOA~G)
    static void JTAG_Set(u8 mode);
    static void delay_us(u32 nus);
    static void delay_ms(u16 nms);
    //////////////////////////////////////////////////////////////////////////////
    //以下为汇编函数
    static void WFI_SET();		//执行WFI指令
    static void INTX_DISABLE();//关闭所有中断
    static void INTX_ENABLE();	//开启所有中断
    static void MSR_MSP(uint32_t addr);	//设置堆栈地址


} sys;



/////////////////////////////////////////////////////////////////  

#endif











