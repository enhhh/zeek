//
//  GameObjectMgr.h
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#ifndef __zeek__GameObjectMgr__
#define __zeek__GameObjectMgr__

#include "GameObject.h"
#include "preInclude.h"
//只交由游戏场景作为成员变量使用
class GameObjectMgr
{
public:
    
    GameObjectMgr();
    
    ~GameObjectMgr();
    
    GameObject* getGameObjectWithCoord(Vec2 coord);
    
    void pushGameObject(GameObject* obj);
    
    bool removeGameObjectFromMap(GameObject *obj);
    
    bool removeGameObjectFromMap(Vec2 coord);
    
protected:
    std::vector<GameObject*> m_objects;
};

#endif /* defined(__zeek__GameObjectMgr__) */
