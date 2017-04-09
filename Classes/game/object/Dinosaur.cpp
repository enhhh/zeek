//
//  Dinosaur.cpp
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#include "Dinosaur.h"
#include "dataStruct.h"
#include "GameMgr.h"

#define NORMAL_REST_TIME 0.5f
#define READY_KILL_PLAYER_TIME 2.0f

Dinosaur::Dinosaur()
: m_restCountDown(NORMAL_REST_TIME)
, m_currentDirection(direction_south)
{
    m_isDestructible = false;
    m_isMoveable = false;
}

Dinosaur * Dinosaur::create(cocos2d::Vec2 coord)
{
    auto ptr = new Dinosaur();
    if(ptr && ptr->init(tiledGid_dinosaur, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    
    return nullptr;
}

bool Dinosaur::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
{
    if(!GameObject::init(gid, bodyArmature, coord))
        return false;
    if(!bodyArmature)
    {
        m_bodyArmature = Armature::create("dinosaur");
        if(m_bodyArmature)
        {
            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            this->addChild(m_bodyArmature);
            playAnimation(false, direction_south);
        }
    }
    scheduleUpdate();
    return true;
}

void Dinosaur::update(float delta)
{
    auto oldState = m_currentState;
    auto oldDirection = m_currentDirection;
    do
    {
        if(m_restCountDown > 0)
        {
            m_restCountDown -= delta;
            break;
        }
        
        if(!checkAround())
        {
            m_currentState = false;
            break;
        }
        
        if(!checkCurrent())
        {
            m_currentState = false;
            if(!m_readyKillPlayer)
                turnDirection();
            return;
        }
        else
        {
            m_currentState = true;
            move(m_currentDirection);
        }
    }while(0);
    if (oldState != m_currentState || oldDirection != m_currentDirection)
    {
        playAnimation(m_currentState, m_currentDirection);
    }
}

void Dinosaur::playAnimation(bool state, Enum_Direction dir)
{
    if(state)
    {
        switch (dir) {
            case direction_east:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_walk_east]);
                break;
            case direction_north:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_walk_north]);
                break;
            case direction_west:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_walk_west]);
                break;
            case direction_south:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_walk_south]);
                break;
            default:
                break;
        }
    }
    else
    {
        switch (dir) {
            case direction_east:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_idle_east]);
                break;
            case direction_north:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_idle_north]);
                break;
            case direction_west:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_idle_west]);
                break;
            case direction_south:
                m_bodyArmature->getAnimation()->play(DinosaurAniStr[DinosaurAniIndex::dinosaur_idle_south]);
                break;
            default:
                break;
        }
    }
}

bool Dinosaur::checkCurrent()
{
    auto obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + DirectVector[m_currentDirection]);
    if(obj)
    {
        if (m_readyKillPlayer == obj)
        {
            GameMgr::getInstance()->removeGameObjectFromMap(obj);
            return true;
        }
        if(obj->m_tiledGid == tiledGid_zeed)
        {
            m_restCountDown = READY_KILL_PLAYER_TIME;
            m_readyKillPlayer = obj;
            return false;
        }
        if (obj->m_isDestructible)
        {
            GameMgr::getInstance()->removeGameObjectFromMap(obj);
            return true;
        }
        
        m_restCountDown = NORMAL_REST_TIME;
        m_readyKillPlayer = nullptr;
        return false;
    }
    
    m_readyKillPlayer = nullptr;
    return true;

}

bool Dinosaur::checkAround()
{
    GameObject *obj = nullptr;
    do
    {
        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(0,-1));
        if(!obj || obj->m_tiledGid == tiledGid_zeed)
            return true;
        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(0,1));
        if(!obj || obj->m_tiledGid == tiledGid_zeed)
            return true;
        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(1,0));
        if(!obj || obj->m_tiledGid == tiledGid_zeed)
            return true;
        obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + Vec2(-1,0));
        if(!obj || obj->m_tiledGid == tiledGid_zeed)
            return true;
    }while (0);
    return false;
}

void Dinosaur::turnDirection()
{
    auto left = DirectVector[m_currentDirection].rotateByAngle(Vec2::ZERO, -M_PI_2);
    auto obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + left);
    if(!obj || obj->m_isDestructible)
    {
        turnLeft();
        return;
    }
    auto right = DirectVector[m_currentDirection].rotateByAngle(Vec2::ZERO, M_PI_2);
    obj = GameMgr::getInstance()->getGameObjectWithCoord(m_coord + right);
    if (!obj || obj->m_isDestructible)
    {
        turnRight();
        return;
    }
    turnBack();
}

void Dinosaur::turnLeft()
{
    switch (m_currentDirection)
    {
        case direction_west:
            m_currentDirection = direction_south;
            break;
        case direction_south:
            m_currentDirection = direction_east;
            break;
        case direction_east:
            m_currentDirection = direction_north;
            break;
        case direction_north:
            m_currentDirection = direction_west;
            break;
        default:
            break;
    }
}

void Dinosaur::turnRight()
{
    switch (m_currentDirection)
    {
        case direction_west:
            m_currentDirection = direction_north;
            break;
        case direction_south:
            m_currentDirection = direction_west;
            break;
        case direction_east:
            m_currentDirection = direction_south;
            break;
        case direction_north:
            m_currentDirection = direction_east;
            break;
        default:
            break;
    }
    
}

void Dinosaur::turnBack()
{
    switch (m_currentDirection)
    {
        case direction_west:
            m_currentDirection = direction_east;
            break;
        case direction_south:
            m_currentDirection = direction_north;
            break;
        case direction_east:
            m_currentDirection = direction_west;
            break;
        case direction_north:
            m_currentDirection = direction_south;
            break;
        default:
            break;
    }
}

bool Dinosaur::move(Enum_Direction dir,GameObject *pusher)
{
    if(m_isMoving)
        return false;
    
    Vec2 targetVec = m_coord;
    
    switch (dir) {
        case Enum_Direction::direction_east:
            targetVec += Vec2(1, 0);
            break;
        case Enum_Direction::direction_west:
            targetVec += Vec2(-1,0);
            break;
        case Enum_Direction::direction_north:
            targetVec += Vec2(0,-1);
            break;
        case Enum_Direction::direction_south:
            targetVec += Vec2(0,1);
            break;
        default:
            break;
    }
    if(targetVec.x < 0
       || targetVec.y < 0
       || targetVec.x > GameMgr::getInstance()->getMapSize().width
       || targetVec.y > GameMgr::getInstance()->getMapSize().height)
        return false;
    auto obj = GameMgr::getInstance()->getGameObjectWithCoord(targetVec);
    if(obj)
        return false;
    m_coord = targetVec;
    m_isMoving = true;
    
    auto endcall = [=](){ m_isMoving = false;};
    this->runAction(Sequence::create(
                                     MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(targetVec))
                                     , CallFunc::create(endcall), nullptr));
    
    return true;

}
