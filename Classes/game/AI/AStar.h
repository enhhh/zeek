//
//  AStar.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__AStar__
#define __zeek__AStar__

#include "preInclude.h"

typedef struct tagAstartListNode
{
    //结点坐标
    Vec2 coordinate;
    
    // 当前结点到起始结点的代价
    short f;
    
    // 当前结点到目标结点的代价
    short g;
    
    // 总代价
    short h;
    
    // 当前结点父结点
    struct tagAstartListNode* father;
    
    // 当前结点子结点
    struct tagAstartListNode* next;
    
}AstartListNode;

// A*算法结构
typedef struct tagAstar
{
    // open 表
    AstartListNode* openHead;
    
    // closed 表
    AstartListNode* closedHead;
} Astar;


class PathFind
{
public:
    
    PathFind();
    ~PathFind();
    
    // 路径长度
    int astarPathCount;
    
    // 路经表
    std::list<Vec2> astarPathList;
    
    TMXTiledMap* tiledMap;
    
    int startX;
    int startY;
    int endX;
    int endY;
    
    static PathFind* getInstance();
    
    // A*初始化
    Astar* newAstar();
    
    // A*释放
    void deleteAstar(Astar* Astar);
    
    // 结点初始化
    void AstarNodeInit(AstartListNode* current, AstartListNode* father, int x, int y, int endX, int endY);
    
    // 取得成本最小的结点
    AstartListNode* AstarGetMinCostList(Astar* Astar);
    
    // 添加结点到链表
    void AstarAddNode(AstartListNode* head, AstartListNode* node);
    
    // 从链表中删除结点
    void AstarRemoveNode(AstartListNode* head, AstartListNode* node);
    
    // 检查Tile是否在链表中
    bool AstarCheckNodeInList(int x, int y, AstartListNode* head);
    
    // 检查Tile是否是地图的路障
    bool AstarIsBlock(int x, int y);
    
    bool AStarSearch(TMXTiledMap* tiledMap, int startX, int startY, int endX, int endY);
};

#endif /* defined(__zeek__AStar__) */
