// Astar.c

#include "Astar.h"

int getBatteryLevel(void) {
    // ����Ӧ����ʵ�ʵĵ���������
    return 50; // �������Ϊ50%
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
        // ���ƻ������ƶ���node->x, node->y
        // ������Ҫ���ʵ�ʵĻ������ƶ�����
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
        // �ҵ�openList��fֵ��С�Ľڵ�
        int minIndex = 0;
        for (int i = 1; i < openListSize; i++) {
            if (openList[i].f < openList[minIndex].f) {
                minIndex = i;
            }
        }

        Node currentNode = openList[minIndex];
        // ��openList���Ƴ�
        for (int i = minIndex; i < openListSize - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListSize--;

        // ��ӵ�closedList
        closedList[closedListSize++] = currentNode;

        // �������Ŀ��ڵ�
        if (currentNode.x == goalX && currentNode.y == goalY) {
            reconstructPath(&closedList[closedListSize - 1]);
            return;
        }

        // �������ڽڵ�
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int newX = currentNode.x + directions[i][0];
            int newY = currentNode.y + directions[i][1];

            // ����Ƿ��ڵ�ͼ��Χ��
            if (newX < 0 || newX >= MAP_WIDTH || newY < 0 || newY >= MAP_HEIGHT) {
                continue;
            }

            // ����Ƿ���closedList��
            if (findNodeInList(closedList, closedListSize, newX, newY) != NULL) {
                continue;
            }

            int tentativeG = currentNode.g + 1;
            Node* neighbor = findNodeInList(openList, openListSize, newX, newY);
            if (neighbor == NULL) {
                // ��ӵ�openList
                Node newNode = {newX, newY, tentativeG, heuristic(newX, newY, goalX, goalY), 0, &closedList[closedListSize - 1]};
                newNode.f = newNode.g + newNode.h;
                openList[openListSize++] = newNode;
            } else if (tentativeG < neighbor->g) {
                // ���½ڵ�
                neighbor->g = tentativeG;
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = &closedList[closedListSize - 1];
            }
        }
    }
}
