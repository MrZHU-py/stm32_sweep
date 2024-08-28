/*
 * @FilePath: \stm32_sweep\Hardware\Astar.h
 * @Author: ZPY
 * @Date: 2024-08-28 09:26:57
 * @TODO: 
 */
// Astar.h

#ifndef ASTAR_H
#define ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// �����ͼ��С�ͳ����λ��
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define CHARGER_X 0
#define CHARGER_Y 0

// ����ڵ�ṹ
typedef struct Node {
    int x, y;
    int g, h, f;
    struct Node* parent;
} Node;

// ���������⺯����������һ���������Ի�ȡ������
int getBatteryLevel(void);

// A*�㷨�ĸ�������
int heuristic(int x1, int y1, int x2, int y2);

Node* findNodeInList(Node* list, int size, int x, int y);

void reconstructPath(Node* node);

void aStar(int startX, int startY, int goalX, int goalY);

#endif // A_STAR_H
