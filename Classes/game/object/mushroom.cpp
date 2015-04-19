//
//  mushroom.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "mushroom.h"
#include "Zeek.h"
#include "GameMgr.h"

Mushroom::Mushroom()
: m_isPoison(false)
{
    m_isDestructible = true;
    m_isMoveable = false;
}

Mushroom* Mushroom::create(cocos2d::Vec2 coord, bool poison)
{
    auto ptr = new Mushroom();
    if(ptr&&ptr->init(poison?tiledGid_poisonousMushroom:tiledGid_healthyMushroom, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}
bool Mushroom::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("mushroom");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            if(m_tiledGid == tiledGid_healthyMushroom)
            {
                m_isPoison = false;
                m_bodyArmature->getAnimation()->play("healthMushroom");
            }
            else
            {
                m_isPoison = true;
                m_bodyArmature->getAnimation()->play("poisonMushroom");
            }
            
        }
    }
    return true;
}


bool Mushroom::move(Enum_Direction dir,GameObject *pusher)
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