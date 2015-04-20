//
//  Bomb.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "Bomb.h"
#include "GameMgr.h"

Bomb::Bomb()
: m_destroyCountDown(5.0f)
, m_isDestroying(false)
{
    m_isDestructible = false;
    m_isMoveable = true;
}

Bomb * Bomb::create(cocos2d::Vec2 coord)
{
    auto ptr = new Bomb();
    if(ptr&& ptr->init(tiledGid_bomb, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool Bomb::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("bomb");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("bomb_normal");
            
            auto movementCallFunc = [=](Armature *armature, MovementEventType movementType, const std::string& movementID)
            {
                if (movementType == MovementEventType::COMPLETE && movementID == "bomb_explode")
                {
                    GameObject* obj = nullptr;
                    do
                    {
                        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(0,-1));
                        if(obj && obj->m_isDestructible)
                        {
                            GameMgr::getInstance()->removeGameObjectFromMap(obj);
                            obj = nullptr;
                        }
                        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(0,1));
                        if(obj && obj->m_isDestructible)
                        {
                            GameMgr::getInstance()->removeGameObjectFromMap(obj);
                            obj = nullptr;
                        }
                        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(1,0));
                        if(obj && obj->m_isDestructible)
                        {
                            GameMgr::getInstance()->removeGameObjectFromMap(obj);
                            obj = nullptr;
                        }
                        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(-1,0));
                        if(obj && obj->m_isDestructible)
                        {
                            GameMgr::getInstance()->removeGameObjectFromMap(obj);
                            obj = nullptr;
                        }
                    }while (0);
                    GameMgr::getInstance()->removeGameObjectFromMap(this);
                }
                
            };
            
            m_bodyArmature->getAnimation()->setMovementEventCallFunc(movementCallFunc);
            
        }
    }
    
    return true;
}

bool Bomb::move(Enum_Direction dir,GameObject *pusher)
{
    if(!m_isDestroying)
    {
        scheduleUpdate();
        m_isDestroying = true;
        m_bodyArmature->getAnimation()->play("bomb_countDown");
    }
    return GameObject::move(dir, pusher);
};

void Bomb::update(float delta)
{
    m_destroyCountDown -= delta;
    if(m_destroyCountDown <= 0)
    {
        m_bodyArmature->getAnimation()->play("bomb_explode");
        unscheduleUpdate();
    }
}
