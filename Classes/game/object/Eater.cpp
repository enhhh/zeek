//
//  Eater.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "Eater.h"
#include "AI/stateMachine/EaterState.h"

Eater::Eater()
: m_chewing(nullptr)
, m_currentState(false)
, m_currentAni(eater_ani_end)
{
    
}

Eater::~Eater()
{
    delete m_stateMachine;
}

Eater * Eater::create(cocos2d::Vec2 coord,bool state)
{
    auto ptr = new Eater();
    
    if(ptr && ptr->init(state?tiledGid_openEater:tiledGid_closeEater, nullptr, coord))
    {
        ptr->m_currentState = state;
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool Eater::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("eater");
        m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        this->addChild(m_bodyArmature);
    }
    
    m_stateMachine = new StateMachine<Eater>(this);
	m_stateMachine->changeState(EaterOpenState::getInstance());
    return true;
}

void Eater::playAnimationWithIndex(EaterAniIndex idx)
{
    
}