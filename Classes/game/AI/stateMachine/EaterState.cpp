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
    if(pOwner->m_isPlayingAnimation)
        return;
    auto coord = pOwner->m_coord;
    //上方判断
    Enum_Direction dir = Enum_Direction::direction_east;
    
    GameObject* obj = nullptr;
    do
    {
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,-1));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_north;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,1));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_south;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(1,0));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_east;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(-1,0));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_west;
            break;
        }
        obj = nullptr;
    }while (0);
    
    if(obj)
    {
        if(obj->m_tiledGid == tiledGid_apple)
        {
        switch (dir) {
            case direction_east:
                pOwner->playAnimationWithIndex(eat_apple_east);
                break;
            case direction_west:
                pOwner->playAnimationWithIndex(eat_apple_west);
                break;
            case direction_south:
                pOwner->playAnimationWithIndex(eat_apple_south);
                break;
            case direction_north:
                pOwner->playAnimationWithIndex(eat_apple_north);
                break;
            default:
                break;
        }
        }else if(obj->m_tiledGid == tiledGid_zeed)
        {
            switch (dir) {
                case direction_east:
                    pOwner->playAnimationWithIndex(eat_zeek_east);
                    break;
                case direction_west:
                    pOwner->playAnimationWithIndex(eat_zeek_west);
                    break;
                case direction_south:
                    pOwner->playAnimationWithIndex(eat_zeek_south);
                    break;
                case direction_north:
                    pOwner->playAnimationWithIndex(eat_zeek_north);
                    break;
                default:
                    break;
            }
        }else if(obj-> m_tiledGid == tiledGid_bugApple)
        {
            switch (dir) {
                case direction_east:
                    pOwner->playAnimationWithIndex(eater_bugApple_east);
                    break;
                case direction_west:
                    pOwner->playAnimationWithIndex(eater_bugApple_west);
                    break;
                case direction_south:
                    pOwner->playAnimationWithIndex(eater_bugApple_south);
                    break;
                case direction_north:
                    pOwner->playAnimationWithIndex(eater_bugApple_north);
                    break;
                default:
                    break;
            }
        }
        GameMgr::getInstance()->removeGameObjectFromMap(obj);
        pOwner->m_stateMachine->changeState(EaterChewState::getInstance());
        return;
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
    pOwner->playAnimationWithIndex(EaterAniIndex::eater_closed);
}

void EaterClosedState::execute(float delta, Eater *pOwner)
{
    auto coord = pOwner->m_coord;
    //上方判断
    Enum_Direction dir = Enum_Direction::direction_east;
    
    GameObject* obj = nullptr;
    do
    {
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,-1));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed) )
        {
            dir = direction_west;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,1));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed) )
        {
            dir = direction_east;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(1,0));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_south;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(-1,0));
        if(obj && (obj->m_tiledGid == tiledGid_apple ||obj->m_tiledGid == tiledGid_bugApple
                   ||obj->m_tiledGid == tiledGid_zeed))
        {
            dir = direction_north;
            break;
        }
        obj = nullptr;
        
    }while (0);
    
    if(obj)
    {
        pOwner->m_stateMachine->changeState(EaterOpenState::getInstance());
    }
}

void EaterClosedState::exit(Eater *pOwner)
{
    
}


static EaterChewState* s_pEaterChewState = nullptr;


EaterChewState::EaterChewState()
{
    
}

EaterChewState* EaterChewState::getInstance()
{
    if(! s_pEaterChewState)
    {
        s_pEaterChewState = new EaterChewState();
    }
    return s_pEaterChewState;
}

void EaterChewState::enter(Eater *pOwner)
{
    
}

void EaterChewState::execute(float delta, Eater *pOwner)
{
    if(pOwner->m_isPlayingAnimation)
        return;
    pOwner->m_stateMachine->changeState(EaterClosedState::getInstance());
}

void EaterChewState::exit(Eater *pOwner)
{
    
}



