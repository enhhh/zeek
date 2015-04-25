//
//  Elected.cpp
//  zeek
//
//  Created by enh on 15/4/24.
//
//

#include "Elected.h"

#include "zeek.h"
#include "GameMgr.h"
Elected::Elected()
{
    m_isDestructible = true;
    m_isMoveable = false;
}

Elected * Elected::create(cocos2d::Vec2 coord)
{
    auto ptr = new Elected();
    if(ptr && ptr->init(tiledGid_elected, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}

bool Elected::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("elected");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("elected");
        }
    }
    return true;
}

bool Elected::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        Zeek *ptr = static_cast<Zeek*>(pusher);
        ptr->m_bodyArmature->setOpacity(110);
        auto action = DelayTime::create(20.0f);
        auto endcall = CallFunc::create([=](){ptr->m_bodyArmature->setOpacity(255);});
        auto seq = Sequence::create(action,endcall, NULL);
        ptr->runAction(seq);
    }
    GameMgr::getInstance()->removeGameObjectFromMap(this);
    return true;
}