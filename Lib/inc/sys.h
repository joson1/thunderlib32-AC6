#ifndef __SYS_H
#define __SYS_H	  
#include <stm32f10x.h>   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ϵͳʱ�ӳ�ʼ�����ʺ�STM32F10xϵ�У�		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2010/1/1
//�汾��V1.9
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.4�޸�˵��
//��NVIC KO��,û��ʹ���κο��ļ�!
//������JTAG_Set����
//V1.5 20120322
//����void INTX_DISABLE(void)��void INTX_ENABLE(void)��������
//V1.6 20120412
//1,����MSR_MSP����												    
//2,�޸�VECT_TAB_RAM��Ĭ��ƫ��,����Ϊ0.
//V1.7 20120818
//1,���ucos֧�����ú�SYSTEM_SUPPORT_UCOS
//2,�޸���ע��
//3,ȥ���˲����ú���BKP_Write
//V1.8 20131120
//1,�޸�ͷ�ļ�Ϊstm32f10x.h,����ʹ��stm32f10x_lib.h�������ͷ�ļ�
//V1.9 20150109
//1,�޸�ͷ�ļ�ΪMY_NVIC_Init�������ִ�����֧�������Ŵ���63���жϵ�����
//2,�޸�WFI_SET/INTX_DISABLE/INTX_ENABLE�Ⱥ�����ʵ�ַ�ʽ
//V2.0 20150322
//�޸�SYSTEM_SUPPORT_UCOSΪSYSTEM_SUPPORT_OS
////////////////////////////////////////////////////////////////////////////////// 	  

//0,��֧��OS
//1,֧��OS
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��OS
																	    

//Ex_NVIC_Configר�ö���
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //�½��ش���
#define RTIR   2  //�����ش���
								   

//JTAGģʽ���ö���
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	


static class _sys
{

private:
    static uint8_t  fac_us;							//us��ʱ������			   
    static uint16_t fac_ms;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
        
    static void delay_init(uint8_t SYSCLK);
    static void MYRCC_DeInit(void);
public:
    static void Clock_Init();  //ʱ�ӳ�ʼ��  
    static void Soft_Reset();      //ϵͳ��λ
    static void Standby();         //����ģʽ 	
    static void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//����ƫ�Ƶ�ַ
    static void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//����NVIC����
    static void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//�����ж�
    static void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//�ⲿ�ж����ú���(ֻ��GPIOA~G)
    static void JTAG_Set(u8 mode);
    static void delay_us(u32 nus);
    static void delay_ms(u16 nms);
    //////////////////////////////////////////////////////////////////////////////
    //����Ϊ��ຯ��
    static void WFI_SET();		//ִ��WFIָ��
    static void INTX_DISABLE();//�ر������ж�
    static void INTX_ENABLE();	//���������ж�
    static void MSR_MSP(uint32_t addr);	//���ö�ջ��ַ


} sys;



/////////////////////////////////////////////////////////////////  

#endif











