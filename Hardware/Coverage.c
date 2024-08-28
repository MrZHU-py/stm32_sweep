/*
 * @FilePath: \stm32_sweep\Hardware\Coverage.c
 * @Author: ZPY
 * @Date: 2024-08-28 09:41:11
 * @TODO: 
 */
#include "Coverage.h"

// ��ʼ����ͼ��0��ʾδ���ǣ�1��ʾ�Ѹ���
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

// ��ʼ��������λ�úͷ���
void initRobot(Robot* robot, int startX, int startY)
{
    robot->x = startX;
    robot->y = startY;
    robot->dir = UP;
}

// ���λ���Ƿ��ڵ�ͼ��Χ��
int isInMap(int x, int y)
{
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}

// ��ȡ��һ��λ��
void getNextPosition(int* x, int* y, Direction dir)
{
    switch (dir) {
        case UP:    (*y)--; break;
        case RIGHT: (*x)++; break;
        case DOWN:  (*y)++; break;
        case LEFT:  (*x)--; break;
    }
}

// ��ת����
Direction rotateDirection(Direction dir)
{
    return (dir + 1) % 4;
}

// �����㷨
void coverage(int map[MAP_WIDTH][MAP_HEIGHT], Robot* robot)
{
    // ʹ��ջ��ʵ�������������
    typedef struct
	{
        int x, y;
        Direction dir;
    } StackNode;

    StackNode stack[MAP_WIDTH * MAP_HEIGHT];
    int top = -1;

    // ����ʼλ����ջ
    stack[++top] = (StackNode){robot->x, robot->y, robot->dir};

    while (top >= 0)
	{
        StackNode current = stack[top--];
        robot->x = current.x;
        robot->y = current.y;
        robot->dir = current.dir;

        // ��ǵ�ǰλ��Ϊ�Ѹ���
        map[robot->x][robot->y] = 1;
        printf("����λ��: (%d, %d)\n", robot->x, robot->y);

        // �����ĸ�����
        for (int i = 0; i < 4; i++)
		{
            int nextX = robot->x;
            int nextY = robot->y;
            getNextPosition(&nextX, &nextY, robot->dir);

            if (isInMap(nextX, nextY) && map[nextX][nextY] == 0)
			{
                // �����һ��λ���ڵ�ͼ��Χ����δ���ǣ�������ջ
                stack[++top] = (StackNode){nextX, nextY, robot->dir};
            }

            // ��ת����
            robot->dir = rotateDirection(robot->dir);
        }
    }
}
