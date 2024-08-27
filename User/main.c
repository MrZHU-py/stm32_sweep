#include "stm32f10x.h"                  // Device header
#include "LEDSEG.h"
#include "Delay.h"
#include "LEDSEG.h"
#include "robot.h"
#include "UltrasonicWave.h"
#include "Key.h"
#include "Serial.h"
#include "timer.h"
#include "Buzzer.h"


int main(void)
{
  int distance;
	Timerx_Init(5000,7199);  //10Khz的计数频率，计数到5000为500ms 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	Key_Init();
	Buzzer_Init();
	LEDSEG_Init();
	UltrasonicWave_Init();      //对超声波模块初始化
	Serial_Init();             // 串口初始化
	robot_Init();              // 机器人初始化
	while(Key_GetNum() == 0);  //等待按键按下
	while (1)
	{
		distance =  UltrasonicWave_StartMeasure();
		printf("测到的距离值为：%d\r\n",distance);

			if(distance<40)
      {
				Buzzer_OFF();
				makerobo_back(70,500);
				makerobo_Right(70,500);
				distance =  UltrasonicWave_StartMeasure();
			}
			else
			{
				makerobo_run(70,1);
				Buzzer_ON();
				
			}
	}
	 
}
