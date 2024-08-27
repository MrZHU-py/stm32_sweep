#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//端口定义
#define IRED_PORT 			GPIOA  
#define IRED_PIN 			  GPIO_Pin_8
#define IRED_PORT_RCC		RCC_APB2Periph_GPIOA

uint32_t IR_Receivecode;	  //定义一个32位数据变量，保存接收码
uint8_t  IR_Receiveflag;   //定义一个8位数据的变量，用于指示接收标志

/*******************************************************************************
* 函 数 名         : IRremote_Init
* 函数功能		     : 红外端口初始化函数	  时钟端口及外部中断初始化 
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void IRremote_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 开启GPIO时钟及管脚复用时钟 */
	RCC_APB2PeriphClockCmd(IRED_PORT_RCC|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=IRED_PIN;                        //红外接收
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(IRED_PORT,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8); //选择GPIO管脚用作外部中断线路
	EXTI_ClearITPendingBit(EXTI_Line8);
	
	/* 设置外部中断的模式 */ 
	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure); 

	/* 设置NVIC参数 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;   //打开全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 	 //响应优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //使能
	NVIC_Init(&NVIC_InitStructure);

}

/*******************************************************************************
* 函 数 名         : IRremote_Counttime
* 函数功能		     : 高电平持续时间，将记录的时间保存在t中返回，其中一次大约20us 
* 输    入         : 无
* 输    出         : t
*******************************************************************************/
uint8_t IRremote_Counttime()
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(IRED_PORT,IRED_PIN)==1)//高电平
	{
		t++;
		Delay_us(20);
		if(t>=250) return t;//超时溢出
	}
	return t;
}

void EXTI9_5_IRQHandler(void)	  //红外遥控外部中断
{
//	uint8_t Tim=0,Ok=0,Data,Num=0;

//	while(1)
//	{
//	  if(GPIO_ReadInputDataBit(IRED_PORT,IRED_PIN)==1)
//		{
//			 Tim=IRremote_Counttime();//获得此次高电平时间

//			 if(Tim>=250) break;//不是有用的信号

//			 if(Tim>=200 && Tim<250)
//			 {
//			 	Ok=1;//收到起始信号
//			 }
//			 else if(Tim>=60 && Tim<90)
//			 {
//			 	Data=1;//收到数据 1
//			 }
//			 else if(Tim>=10 && Tim<50)
//			 {
//			 	Data=0;//收到数据 0
//			 }

//			 if(Ok==1)
//			 {
//			 	IR_Receivecode<<=1;
//				IR_Receivecode+=Data;

//				if(Num>=32)
//				{
//					IR_Receiveflag=1;
//				  break;
//				}
//			 }
//			 Num++;
//		}
//	}
//	EXTI_ClearITPendingBit(EXTI_Line8);	
}
