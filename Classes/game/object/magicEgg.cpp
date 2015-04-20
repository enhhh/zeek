//
//  magicEgg.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "magicEgg.h"
#include "Zeek.h"
#include "GameMgr.h"
#include "Flower.h"
#include "mushroom.h"

MagicEgg::MagicEgg()
{
    m_isDestructible = true;
    m_isMoveable = false;
}

MagicEgg*MagicEgg::create(cocos2d::Vec2 coord)
{
    auto ptr = new MagicEgg();
    
    if(ptr && ptr->init(tiledGid_magicEgg, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool MagicEgg::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("magicEgg");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("egg");
        }
    }
    return true;
}

bool MagicEgg::move(Enum_Direction dir,GameObject *pusher)
{
    if(pusher && pusher->m_tiledGid == tiledGid_zeed)
    {
        switchPoison();
    }
    GameMgr::getInstance()->removeGameObjectFromMap(this);
    return true;
}


void MagicEgg::switchPoison()
{
    const std::vector<GameObject*> &objects = GameMgr::getInstance()->getAllObject();
    
    for(auto obj : objects)
    {
        if (obj->m_tiledGid == tiledGid_healthyFlower || obj->m_tiledGid == tiledGid_poisonFlower) {
            auto flower = static_cast<Flower*>(obj);
            flower->switchPoison();
            continue;
        }
        
        if(obj->m_tiledGid == tiledGid_poisonousMushroom
           || obj->m_tiledGid == tiledGid_healthyMushroom)
        
        {
            auto mushroom = static_cast<Mushroom*>(obj);
            mushroom->switchPoison();
        }
    }
}


