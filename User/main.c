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
#include "Astar.h"
#include "Coverage.h"  // ���������㷨ͷ�ļ�

#include <stdio.h>

int main(void)
{
    int distance;
    Timerx_Init(5000, 7199);  //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
    Key_Init();
    Buzzer_Init();
    LEDSEG_Init();
    UltrasonicWave_Init();      //�Գ�����ģ���ʼ��
    Serial_Init();             // ���ڳ�ʼ��
    robot_Init();              // �����˳�ʼ��
    while (Key_GetNum() == 0);  //�ȴ���������

    // ��ʼ����ͼ�ͻ�����
    int map[MAP_WIDTH][MAP_HEIGHT];
    Robot robot;
    initMap(map);
    initRobot(&robot, 10, 10);  // ��������˴�(10, 10)λ�ÿ�ʼ

    while (1)
    {
        distance = UltrasonicWave_StartMeasure();
        printf("�⵽�ľ���ֵΪ��%d\r\n", distance);

        if (distance < 40)    // �̾���ͺ���ת��
        {
            Buzzer_OFF();
            makerobo_back(70, 500);
            makerobo_Right(70, 900);
            distance = UltrasonicWave_StartMeasure();
        }
        else if (distance < 100)    // �еȾ���ͼ�����ʹ
        {
            makerobo_run(70, 1);
            Buzzer_ON();
        }
        else    // ǰ�����ϰ��������ʹ
        {
            makerobo_run(100, 1);
            Buzzer_ON();
        }

        // ������
        if (getBatteryLevel() < 20) // �����������20%ʱ��Ҫ�س��
        {
            printf("�������㣬��ʼѰ�ҳ����...\n");
            // ��ȡ��ǰ������λ�ã������к������Ի�ȡ��
            int currentX = 10; // ����Ӧ����ʵ�ʵĻ�ȡ������λ�õĴ���
            int currentY = 10; // ����Ӧ����ʵ�ʵĻ�ȡ������λ�õĴ���
            aStar(currentX, currentY, CHARGER_X, CHARGER_Y);
            break; // �ҵ�·�����˳�ѭ��
        }

        // ִ�и����㷨
        coverage(map, &robot);
    }
}
