//
//  Electrode.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "Electrode.h"
#include "AI/stateMachine/ElectrodeState.h"
#include "GameMgr.h"

#define ELECTRODE_DESTORY_COUNTDOWN 3.0f
Electrode::Electrode()
: m_isDestroying(false)
, m_destroyCountDown(ELECTRODE_DESTORY_COUNTDOWN)
{
    m_isMoveable = true;
    m_isDestructible = false;
}

Electrode * Electrode::create(Vec2 coord)
{
    auto ptr = new Electrode();
    if(ptr && ptr->init(tiledGid_electrode, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}



bool Electrode::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("electrode");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            m_bodyArmature->getAnimation()->play("electrode_normal");
        }
    }
    m_stateMachine = new StateMachine<Electrode>(this);
    m_stateMachine->changeState(ElectrodeState::getInstance());
    scheduleUpdate();
    return  true;
}

void Electrode::update(float delta)
{
    if( m_isDestroying)
        m_destroyCountDown -= delta;
    
    m_stateMachine->update(delta);
}

void Electrode::startDestroyCountDown()
{
    m_destroyCountDown = ELECTRODE_DESTORY_COUNTDOWN;
    m_isDestroying = true;
    m_bodyArmature->getAnimation()->play("electrode_destroy");
}

void Electrode::stopDestroyCountDown()
{
    m_destroyCountDown = ELECTRODE_DESTORY_COUNTDOWN;
    m_isDestroying = false;
    m_bodyArmature->getAnimation()->play("electrode_normal");
}

void Electrode::destroySelf()
{
    GameMgr::getInstance()->removeGameObjectFromMap(this);
}