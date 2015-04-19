//
//  Apple.cpp
//  zeek
//
//  Created by enh on 15/4/18.
//
//

#include "Apple.h"

Apple::Apple()
: m_hasBug(false)
{
    m_isMoveable = true;
    m_isDestructible = true;
}


Apple::~Apple()
{
    
}

Apple * Apple::create(cocos2d::Vec2 coord, bool hasBug)
{
    auto ptr = new Apple();
    if(ptr && ptr->init(hasBug?tiledGid_bugApple:tiledGid_apple, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    
    return nullptr;
}

bool Apple::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("apple");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
        }
        if(gid == tiledGid_bugApple)
        {
            m_bodyArmature->getAnimation()->play("bugApple");
            m_hasBug = true;
        }
        else
            m_bodyArmature->getAnimation()->play("helthApple");
    }
    return  true;
}

