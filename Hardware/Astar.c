// Astar.c

#include "Astar.h"

int getBatteryLevel(void) {
    // 这里应该有实际的电量检测代码
    return 50; // 假设电量为50%
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

Node* findNodeInList(Node* list, int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        if (list[i].x == x && list[i].y == y) {
            return &list[i];
        }
    }
    return NULL;
}

void reconstructPath(Node* node) {
    while (node != NULL) {
        printf("Path: (%d, %d)\n", node->x, node->y);
        // 控制机器人移动到node->x, node->y
        // 这里需要添加实际的机器人移动代码
        node = node->parent;
    }
}

void aStar(int startX, int startY, int goalX, int goalY) {
    Node openList[MAP_WIDTH * MAP_HEIGHT];
    Node closedList[MAP_WIDTH * MAP_HEIGHT];
    int openListSize = 0;
    int closedListSize = 0;

    Node startNode = {startX, startY, 0, heuristic(startX, startY, goalX, goalY), 0, NULL};
    startNode.f = startNode.g + startNode.h;
    openList[openListSize++] = startNode;

    while (openListSize > 0) {
        // 找到openList中f值最小的节点
        int minIndex = 0;
        for (int i = 1; i < openListSize; i++) {
            if (openList[i].f < openList[minIndex].f) {
                minIndex = i;
            }
        }

        Node currentNode = openList[minIndex];
        // 从openList中移除
        for (int i = minIndex; i < openListSize - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListSize--;

        // 添加到closedList
        closedList[closedListSize++] = currentNode;

        // 如果到达目标节点
        if (currentNode.x == goalX && currentNode.y == goalY) {
            reconstructPath(&closedList[closedListSize - 1]);
            return;
        }

        // 处理相邻节点
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int newX = currentNode.x + directions[i][0];
            int newY = currentNode.y + directions[i][1];

            // 检查是否在地图范围内
            if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT) {
                continue;
            }

            // 检查是否在closedList中
            if (findNodeInList(closedList, closedListSize, newX, newY) != NULL) {
                continue;
            }

            int tentativeG = currentNode.g + 1;
            Node* neighbor = findNodeInList(openList, openListSize, newX, newY);
            if (neighbor == NULL) {
                // 添加到openList
                Node newNode = {newX, newY, tentativeG, heuristic(newX, newY, goalX, goalY), 0, &closedList[closedListSize - 1]};
                newNode.f = newNode.g + newNode.h;
                openList[openListSize++] = newNode;
            } else if (tentativeG < neighbor->g) {
                // 更新节点
                neighbor->g = tentativeG;
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = &closedList[closedListSize - 1];
            }
        }
    }
}
