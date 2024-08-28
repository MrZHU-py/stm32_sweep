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
#include "Coverage.h"  // 包含覆盖算法头文件

#include <stdio.h>

int main(void)
{
    int distance;
    Timerx_Init(5000, 7199);  //10Khz的计数频率，计数到5000为500ms 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
    Key_Init();
    Buzzer_Init();
    LEDSEG_Init();
    UltrasonicWave_Init();      //对超声波模块初始化
    Serial_Init();             // 串口初始化
    robot_Init();              // 机器人初始化
    while (Key_GetNum() == 0);  //等待按键按下

    // 初始化地图和机器人
    int map[MAP_WIDTH][MAP_HEIGHT];
    Robot robot;
    initMap(map);
    initRobot(&robot, 10, 10);  // 假设机器人从(10, 10)位置开始

    while (1)
    {
        distance = UltrasonicWave_StartMeasure();
        printf("测到的距离值为：%d\r\n", distance);

        if (distance < 40)    // 短距离就后退转弯
        {
            Buzzer_OFF();
            makerobo_back(70, 500);
            makerobo_Right(70, 900);
            distance = UltrasonicWave_StartMeasure();
        }
        else if (distance < 100)    // 中等距离就减速行使
        {
            makerobo_run(70, 1);
            Buzzer_ON();
        }
        else    // 前方无障碍则快速行使
        {
            makerobo_run(100, 1);
            Buzzer_ON();
        }

        // 检测电量
        if (getBatteryLevel() < 20) // 假设电量低于20%时需要回充电
        {
            printf("电量不足，开始寻找充电器...\n");
            // 获取当前机器人位置（假设有函数可以获取）
            int currentX = 10; // 这里应该有实际的获取机器人位置的代码
            int currentY = 10; // 这里应该有实际的获取机器人位置的代码
            aStar(currentX, currentY, CHARGER_X, CHARGER_Y);
            break; // 找到路径后退出循环
        }

        // 执行覆盖算法
        coverage(map, &robot);
    }
}
