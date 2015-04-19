//
//  Key.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "Key.h"
#include "zeek.h"
#include "GameMgr.h"
Key::Key()
{
    
}

Key * Key::create(cocos2d::Vec2 coord)
{
    auto ptr = new Key();
    if(ptr && ptr->init(tiledGid_key, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}

bool Key::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("key");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("key");
        }
    }
    return true;
}

bool Key::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        Zeek *ptr = static_cast<Zeek*>(pusher);
        ptr->m_keys++;
    }
    GameMgr::getInstance()->removeGameObjectFromMap(this);
    return true;
}