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

// 定义地图大小和充电器位置
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define CHARGER_X 0
#define CHARGER_Y 0

// 定义节点结构
typedef struct Node {
    int x, y;
    int g, h, f;
    struct Node* parent;
} Node;

// 定义电量检测函数（假设有一个函数可以获取电量）
int getBatteryLevel(void);

// A*算法的辅助函数
int heuristic(int x1, int y1, int x2, int y2);

Node* findNodeInList(Node* list, int size, int x, int y);

void reconstructPath(Node* node);

void aStar(int startX, int startY, int goalX, int goalY);

#endif // A_STAR_H
