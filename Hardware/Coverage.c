/*
 * @FilePath: \stm32_sweep\Hardware\Coverage.c
 * @Author: ZPY
 * @Date: 2024-08-28 09:41:11
 * @TODO: 
 */
#include "Coverage.h"

// 初始化地图，0表示未覆盖，1表示已覆盖
void initMap(int map[MAP_WIDTH][MAP_HEIGHT])
{
    for (int i = 0; i < MAP_WIDTH; i++)
	{
        for (int j = 0; j < MAP_HEIGHT; j++)
		{
            map[i][j] = 0;
        }
    }
}

// 初始化机器人位置和方向
void initRobot(Robot* robot, int startX, int startY)
{
    robot->x = startX;
    robot->y = startY;
    robot->dir = UP;
}

// 检查位置是否在地图范围内
int isInMap(int x, int y)
{
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}

// 获取下一个位置
void getNextPosition(int* x, int* y, Direction dir)
{
    switch (dir) {
        case UP:    (*y)--; break;
        case RIGHT: (*x)++; break;
        case DOWN:  (*y)++; break;
        case LEFT:  (*x)--; break;
    }
}

// 旋转方向
Direction rotateDirection(Direction dir)
{
    return (dir + 1) % 4;
}

// 覆盖算法
void coverage(int map[MAP_WIDTH][MAP_HEIGHT], Robot* robot)
{
    // 使用栈来实现深度优先搜索
    typedef struct
	{
        int x, y;
        Direction dir;
    } StackNode;

    StackNode stack[MAP_WIDTH * MAP_HEIGHT];
    int top = -1;

    // 将初始位置入栈
    stack[++top] = (StackNode){robot->x, robot->y, robot->dir};

    while (top >= 0)
	{
        StackNode current = stack[top--];
        robot->x = current.x;
        robot->y = current.y;
        robot->dir = current.dir;

        // 标记当前位置为已覆盖
        map[robot->x][robot->y] = 1;
        printf("覆盖位置: (%d, %d)\n", robot->x, robot->y);

        // 尝试四个方向
        for (int i = 0; i < 4; i++)
		{
            int nextX = robot->x;
            int nextY = robot->y;
            getNextPosition(&nextX, &nextY, robot->dir);

            if (isInMap(nextX, nextY) && map[nextX][nextY] == 0)
			{
                // 如果下一个位置在地图范围内且未覆盖，将其入栈
                stack[++top] = (StackNode){nextX, nextY, robot->dir};
            }

            // 旋转方向
            robot->dir = rotateDirection(robot->dir);
        }
    }
}
