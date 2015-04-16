//
//  EaterState.cpp
//  zeek
//
//  Created by enh on 15/4/15.
//
//

#include "EaterState.h"
#include "GameMgr.h"

static EaterOpenState * s_pEaterOpenState = nullptr;

EaterOpenState::EaterOpenState()
{
    
}

EaterOpenState *EaterOpenState::getInstance()
{
    if(!s_pEaterOpenState)
    {
        s_pEaterOpenState = new EaterOpenState();
    }
    return s_pEaterOpenState;
}

void EaterOpenState::enter(Eater *pOwner)
{
    pOwner->playAnimationWithIndex(EaterAniIndex::eater_open);
}

void EaterOpenState::execute(float delta, Eater *pOwner)
{
    auto coord = pOwner->m_coord;
    //上方判断
    GameObject* obj = nullptr;
    obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,-1));
    if(obj)
    {
        if(obj->m_tiledGid == tiledGid_apple)
            pOwner->playAnimationWithIndex(eat_apple_north);
    }
    
    
    
}

void EaterOpenState::exit(Eater *pOwner)
{
    
}

static EaterClosedState* s_pEaterClosedState = nullptr;

EaterClosedState::EaterClosedState()
{
    
}

EaterClosedState *EaterClosedState::getInstance()
{
    if(! s_pEaterClosedState)
    {
        s_pEaterClosedState = new EaterClosedState();
    }
    return s_pEaterClosedState;
}

void EaterClosedState::enter(Eater *pOwner)
{
    
}

void EaterClosedState::execute(float delta, Eater *pOwner)
{
    
}

void EaterClosedState::exit(Eater *pOwner)
{
    
}

