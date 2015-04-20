//
//  Flower.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "Flower.h"
#include "Zeek.h"
#include "GameMgr.h"

Flower::Flower()
: m_isPoison(false)
{
    m_isMoveable = false;
    m_isDestructible = true;
}

Flower * Flower::create(cocos2d::Vec2 coord, bool poison)
{
    auto ptr = new Flower();
    
    if(ptr && ptr->init(poison?tiledGid_poisonFlower:tiledGid_healthyFlower, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool Flower::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(gid == tiledGid_healthyFlower)
        m_isPoison = false;
    else
        m_isPoison = true;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("flower");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            if(m_isPoison)
                m_bodyArmature->getAnimation()->play("poisonFlower");
            else
                m_bodyArmature->getAnimation()->play("healthFlower");
        }
    }
    return true;
}

void Flower::switchPoison()
{
    if(m_isPoison)
    {
        m_isPoison = false;
        m_tiledGid = tiledGid_healthyFlower;
        m_bodyArmature->getAnimation()->play("healthFlower");
    }
    else
    {
        m_isPoison = true;
        m_tiledGid = tiledGid_poisonFlower;
        m_bodyArmature->getAnimation()->play("poisonFlower");
    }
}

bool Flower::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        Zeek *ptr = static_cast<Zeek*>(pusher);
        //加分
    }
    GameMgr::getInstance()->removeGameObjectFromMap(this);
    return true;
}