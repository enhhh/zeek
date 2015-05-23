//
//  AStar.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "AStar.h"

PathFind::PathFind()
{
}

PathFind::~PathFind()
{
}

static PathFind* pathFind = NULL;

PathFind* PathFind::getInstance()
{
    if (!pathFind)
    {
        pathFind = new PathFind();
    }
    
    return pathFind;
}

// A*初始化
Astar* PathFind::newAstar()
{
    Astar* astar = (Astar*)malloc(sizeof(Astar));
    astar->openHead = (AstartListNode*)malloc(sizeof(AstartListNode));
    astar->closedHead = (AstartListNode*)malloc(sizeof(AstartListNode));
    astar->openHead->next = NULL;
    astar->closedHead->next = NULL;
    return astar;
}

// A*释放
void PathFind::deleteAstar(Astar* astar)
{
    while (astar->openHead != NULL)
    {
        AstartListNode* t = astar->openHead;
        astar->openHead = astar->openHead->next;
        free(t);
        t = NULL;
    }
    
    while (astar->closedHead != NULL)
    {
        AstartListNode* t = astar->closedHead;
        astar->closedHead = astar->closedHead->next;
        free(t);
        t = NULL;
    }
    
    free(astar);
}

// 结点初始化
void PathFind::AstarNodeInit(AstartListNode* current, AstartListNode* father, int x, int y, int endX, int endY)
{
    current->coordinate.x = x;
    current->coordinate.y = y;
    current->father = father;
    current->next = NULL;
    
    if (father != NULL)
    {
        current->f = father->f + 1;
    }
    else
    {
        current->f = 0;
    }
    
    current->g = abs(endX - x) + abs(endY - y);
    current->h = current->f + current->g;
}

// 取得成本最小的结点
AstartListNode* PathFind::AstarGetMinCostList(Astar* astar)
{
    AstartListNode* min = astar->openHead->next;
    AstartListNode* current = min->next;
    
    while (current != NULL)
    {
        if (current->h < min->h)
        {
            min = current;
        }
        
        current = current->next;
    }
    
    return min;
}

// 添加结点到链表
void PathFind::AstarAddNode(AstartListNode* head, AstartListNode* node)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    
    head->next = node;
}

// 从链表中删除结点
void PathFind::AstarRemoveNode(AstartListNode* head, AstartListNode* node)
{
    AstartListNode* current = head;
    head = head->next;
    
    while (head != NULL)
    {
        if (head == node)
        {
            current->next = head->next;
            head->next = NULL;
            break;
        }
        else
        {
            current = head;
            head = head->next;
        }
    }
}

// 检查Tile是否在链表中
bool PathFind::AstarCheckNodeInList(int x, int y, AstartListNode* head)
{
    bool result = false;
    head = head->next;
    
    while (head != NULL)
    {
        if (head->coordinate.x == x && head->coordinate.y == y)
        {
            result = true;
            break;
        }
        else
        {
            head = head->next;
        }
    }
    
    return result;
}

// 检查Tile是否是地图的路障
bool PathFind::AstarIsBlock(int x, int y)
{
    if (x >= 0 && x < tiledMap->getMapSize().width && y >= 0 && y < tiledMap->getMapSize().height)
    {
        TMXLayer* mapLayer = tiledMap->getLayer("hazard");
        unsigned int gid = mapLayer->getTileGIDAt(Vec2(x, y));
        if(gid >= 21 || gid == tiledGid_oil)
        {
            return true;
        }
    }
    else
    {
        return false;
    }
    
    return false;
}

bool PathFind::AStarSearch(TMXTiledMap* tiledMap, int startX, int startY, int endX, int endY)
{
    astarPathCount = 0;
    astarPathList.clear();
    
    this->tiledMap = tiledMap;
    
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
    
    if (AstarIsBlock(endX, endY))
    {
        return false;
    }
    
    int offsetX[] = {0, 0, -1, 1};//只搜索4个方向
    int offsetY[] = {1, -1, 0, 0};
    
    Astar* astar = newAstar();
    
    AstartListNode* currentNode = NULL;
    AstartListNode* startNode = (AstartListNode*)malloc(sizeof(AstartListNode));
    AstarNodeInit(startNode, NULL, startX, startY, endX, endY);
    // 把起始结点加入OpenList
    AstarAddNode(astar->openHead, startNode);
    
    // 如查OpenList不为空
    while (astar->openHead->next != NULL)
    {
        // 取得成本最小的结点
        currentNode = AstarGetMinCostList(astar);
        
        // 如果当前结点是目标结点
        if (currentNode->coordinate.x == endX && currentNode->coordinate.y == endY)
        {
            break;
        }
        else
        {
            // 把当前结点添加到Closed表中
            AstarAddNode(astar->closedHead, currentNode);
            // 把当前结点从Open表中删除
            AstarRemoveNode(astar->openHead, currentNode);
            
            for (int i = 0; i < 4; i++)
            {
                int x = currentNode->coordinate.x + offsetX[i];
                int y = currentNode->coordinate.y + offsetY[i];
                
                if (x < 0 || x >= tiledMap->getMapSize().width || y < 0 || y >= tiledMap->getMapSize().height)
                {
                    continue;
                }
                else
                {
                    if (!AstarCheckNodeInList(x, y, astar->openHead)
                        && !AstarCheckNodeInList(x, y, astar->closedHead)
                        && !AstarIsBlock(x, y)
                        )
                    {
                        AstartListNode* endNode = (AstartListNode*)malloc(sizeof(AstartListNode));
                        AstarNodeInit(endNode, currentNode, x, y, endX, endY);
                        AstarAddNode(astar->openHead, endNode);
                    }
                }
            }
        }
    }
    
    if (astar->openHead->next == NULL && (currentNode->coordinate.x != endX || currentNode->coordinate.y != endY))
    {
        astarPathCount = 0;
        return false;
    }
    else
    {
        while (currentNode != NULL)
        {
            Vec2 tilePoint;
            tilePoint.x = currentNode->coordinate.x;
            tilePoint.y = currentNode->coordinate.y;
            
            TMXLayer* mapLayer = tiledMap->getLayer("ground");
            Sprite* tile = mapLayer->getTileAt(Vec2(tilePoint.x, tilePoint.y));
//            if(tile)
//                tile->setColor(Color3B(255, 0, 0));
            astarPathList.push_front(tilePoint);
            currentNode = currentNode->father;
            astarPathCount++;
        }
        astarPathList.pop_front();
        astarPathCount--;
        if(astarPathList.empty())
            return false;
        return true;
    }
    
    deleteAstar(astar);
    return false;
}