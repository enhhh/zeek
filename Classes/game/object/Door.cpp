//
//  Door.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "Door.h"
#include "Zeek.h"
#include "GameMgr.h"
Door::Door()
{
    m_isDestructible = true;
    m_isMoveable = false;
}

Door * Door::create(cocos2d::Vec2 coord)
{
    auto ptr = new Door();
    if(ptr && ptr->init(tiledGid_door, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool Door::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("door");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("door");
        }
    }
    return true;
}

bool Door::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        Zeek *ptr = static_cast<Zeek*>(pusher);
        if(ptr->m_keys > 0)
        {
            ptr->m_keys--;
            GameMgr::getInstance()->removeGameObjectFromMap(this);
            return true;
        }
    }
    return false;
}