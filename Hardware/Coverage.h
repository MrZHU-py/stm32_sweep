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

// �����ͼ��С
#define MAP_WIDTH 20
#define MAP_HEIGHT 20

// ���巽��
typedef enum
{
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

// ��������˽ṹ
typedef struct
{
    int x, y;
    Direction dir;
} Robot;

// ��ʼ����ͼ�ͻ�����
void initMap(int map[MAP_WIDTH][MAP_HEIGHT]);
void initRobot(Robot* robot, int startX, int startY);

// �����㷨
void coverage(int map[MAP_WIDTH][MAP_HEIGHT], Robot* robot);

#endif // COVERAGE_H
