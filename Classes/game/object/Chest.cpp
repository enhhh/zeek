//
//  Chest.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "Chest.h"
#include "zeek.h"
#include "GameMgr.h"
Chest::Chest()
{
    m_isDestructible = true;
    m_isMoveable = false;
}

Chest * Chest::create(cocos2d::Vec2 coord)
{
    auto ptr = new Chest();
    if(ptr && ptr->init(tiledGid_chest, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}

bool Chest::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("chest");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("chest");
        }
    }
    return true;
}

bool Chest::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        Zeek *ptr = static_cast<Zeek*>(pusher);
        //ptr->m_keys++;
        
        //加分
    }
    GameMgr::getInstance()->removeGameObjectFromMap(this);
    return true;
}