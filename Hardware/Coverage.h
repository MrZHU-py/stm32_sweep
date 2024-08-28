/*
 * @FilePath: \stm32_sweep\Hardware\Coverage.h
 * @Author: ZPY
 * @Date: 2024-08-28 09:41:43
 * @TODO: 
 */
#ifndef COVERAGE_H
#define COVERAGE_H

#include <stdio.h>
#include <stdlib.h>

// 定义地图大小
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

// 定义方向
typedef enum
{
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

// 定义机器人结构
typedef struct
{
    int x, y;
    Direction dir;
} Robot;

// 初始化地图和机器人
void initMap(int map[MAP_WIDTH][MAP_HEIGHT]);
void initRobot(Robot* robot, int startX, int startY);

// 覆盖算法
void coverage(int map[MAP_WIDTH][MAP_HEIGHT], Robot* robot);

#endif // COVERAGE_H
