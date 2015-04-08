//
//  GameObjectMgr.cpp
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#include "GameObjectMgr.h"


GameObjectMgr::GameObjectMgr()
{
    
}

GameObjectMgr::~GameObjectMgr()
{
    m_objects.clear();
}

GameObject* GameObjectMgr::getGameObjectWithCoord(cocos2d::Vec2 coord)
{
    for(auto object : m_objects)
    {
        if(object->m_coord == coord)
            return object;
    }
    
    return nullptr;
}

void GameObjectMgr::pushGameObject(GameObject *obj)
{
    m_objects.push_back(obj);
}

bool GameObjectMgr::removeGameObjectFromMap(GameObject *obj)
{
    for (auto object = m_objects.begin();object != m_objects.end();object++)
    {
        if(*object == obj)
        {
            auto bodySprite = obj->m_bodySprite;
            if(bodySprite)
                bodySprite->removeFromParent();
            m_objects.erase(object);
            return true;
        }
    }
    return false;
}

bool GameObjectMgr::removeGameObjectFromMap(Vec2 coord)
{
    for (auto object = m_objects.begin();object != m_objects.end();object++)
    {
        if((*object)->m_coord == coord)
        {
            auto bodySprite = (*object)->m_bodySprite;
            if(bodySprite)
                bodySprite->removeFromParent();
            m_objects.erase(object);
            return true;
        }
    }
    return false;
}


