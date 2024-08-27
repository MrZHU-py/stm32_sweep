#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "timer.h"


#define	TRIG_PORT      GPIOB		//TRIG       
#define	ECHO_PORT      GPIOB		//ECHO 
#define	TRIG_PIN       GPIO_Pin_15   //TRIG       
#define	ECHO_PIN       GPIO_Pin_14	//ECHO   

float UltrasonicWave_Distance;      //计算出的距离    

/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					  //PB15接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	      //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				   //PB14接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);				 //初始化GPIOB
	
	//GPIOB.14	  中断线以及中断初始化配置
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);

 	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		                         //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
			
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			     //使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	     //抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			       //子优先级2 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						     //使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	                             //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

//------------------------通道14中断函数---------------------------------------------
void EXTI15_10_IRQHandler(void)
{
	Delay_us(10);		                      //延时10us
  if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM2, ENABLE);                                       //开启时钟
		
			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));          //等待低电平

			TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
			UltrasonicWave_Distance=TIM_GetCounter(TIM2)*5*34/200.0;			//计算距离&&UltrasonicWave_Distance<150
			EXTI_ClearITPendingBit(EXTI_Line14);  //清除EXTI1线路挂起位
	}
}
/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
int UltrasonicWave_StartMeasure(void)
{
  int u_temp;
	GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
  Delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	u_temp = UltrasonicWave_Distance*10;
	return u_temp;
}

