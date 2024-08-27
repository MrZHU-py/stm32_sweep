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
	Timerx_Init(5000,7199);  //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	Key_Init();
	Buzzer_Init();
	LEDSEG_Init();
	UltrasonicWave_Init();      //�Գ�����ģ���ʼ��
	Serial_Init();             // ���ڳ�ʼ��
	robot_Init();              // �����˳�ʼ��
	while(Key_GetNum() == 0);  //�ȴ���������
	while (1)
    {
        distance = UltrasonicWave_StartMeasure();
        printf("�⵽�ľ���ֵΪ��%d\r\n", distance);

        if (distance < 20)  // ����С��20cm
        {
            Buzzer_OFF();
            makerobo_stop();       // ֹͣ
            makerobo_back(50, 500); // ��������
            makerobo_Right(50, 500); // ������ת����
        }
        else if (distance < 40)  // ������20cm��40cm֮��
        {
            Buzzer_ON();
            makerobo_run(30, 1);  // ����ǰ��
        }
        else  // �������40cm
        {
            Buzzer_ON();
            makerobo_run(50, 1);  // ����ǰ��
        }
    }
}
