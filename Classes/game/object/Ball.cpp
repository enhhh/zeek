//
//  Ball.cpp
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#include "Ball.h"
#include "zeek.h"
#include "GameMgr.h"
Ball::Ball()
{
    m_isDestructible = false;
    m_isMoveable = true;
}

Ball * Ball::create(cocos2d::Vec2 coord)
{
    auto ptr = new Ball();
    if(ptr && ptr->init(tiledGid_ball, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return ptr;
}

bool Ball::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("ball");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("ball");
        }
    }
    return true;
}