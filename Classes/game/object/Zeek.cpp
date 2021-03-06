//
//  Zeek.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "Zeek.h"
#include "GameMgr.h"
#include "AI/stateMachine/ZeekState.h"

#define ZEEK_SPEED 1

Zeek::Zeek()
: m_stateMachine(nullptr)
, m_isMoving(false)
, m_currentAni(ZeekAniIndex_end)
, m_currentFaceTo(direction_south)
, m_keys(0)
{
    
}

Zeek::~Zeek()
{
    m_movePath.clear();
    delete m_stateMachine;
}

Zeek * Zeek::create(Vec2 coordinate)
{
    auto ptr = new Zeek();
    
    if(ptr && ptr->init(tiledGid_zeed,nullptr,coordinate))
    {
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
}


bool Zeek::init(tiledGid gid,Armature *bodyArmature,Vec2 coord)
{
    GameObject::init(gid, bodyArmature, coord);
    
    m_stateMachine = new StateMachine<Zeek>(this);
    m_stateMachine->changeState(ZeekRestState::getInstance());
    
    //从缓存中读动画
    
    if (!m_bodyArmature)
    {
        m_bodyArmature = Armature::create("zeek");
        m_bodyArmature->getAnimation()->play(ZeekAniStr[ZeekAniIndex::idle_south]);
        this->addChild(m_bodyArmature);
    }
    
    scheduleUpdate();
    return true;
}

bool Zeek::move(Enum_Direction dir)
{
    auto endcall = [=](){ m_isMoving = false;};
    
    auto endAction = CallFunc::create(endcall);
    
    m_currentFaceTo = dir;
    
    Vec2 targetPos =Vec2::ZERO;

    switch (dir)
    {
        case direction_west:
            
            targetPos =m_coord + Vec2(-1, 0);
            break;
        case direction_east:

            targetPos = m_coord + Vec2(1,0);
            break;
        case direction_north:
            targetPos = m_coord + Vec2(0,-1);
            break;
        case direction_south:
            targetPos = m_coord + Vec2(0,1);
            break;
        default:
            break;
    }
    
    auto obj = GameMgr::getInstance()->getGameObjectWithCoord(targetPos);
    if(!obj)
    {
        m_isMoving = true;
        m_coord = targetPos;
        this->runAction(Sequence::create(
                                         MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord))
                                         ,endAction,nullptr));
        return true;
    }
    else
    {
        if (obj->move(dir,this)) {
            m_isMoving = true;
            m_coord = targetPos;
            this->runAction(Sequence::create(
                                             MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord))
                                             ,endAction,nullptr));
            return true;
        }
    }

    return false;
}

cocos2d::Vec2 Zeek::getNextMoveCoord()
{
    if (m_movePath.empty())
        return m_coord;
    auto vec = m_movePath.front();
    m_movePath.pop_front();
    return vec;
}

void Zeek::setFaceTo(Enum_Direction dir)
{
    switch (dir)
    {
        case direction_west:
            m_currentAni = ZeekAniIndex::idle_west;
            break;
        case direction_east:
            m_currentAni = ZeekAniIndex::idle_east;
            break;
        case direction_north:
            m_currentAni = ZeekAniIndex::idle_north;
            break;
        case direction_south:
            m_currentAni = ZeekAniIndex::idle_south;
            break;
        default:
            m_currentAni = ZeekAniIndex::idle_south;
            break;
    }
    m_bodyArmature->getAnimation()->play(ZeekAniStr[m_currentAni]);
    
}

void Zeek::playAnimationWithIndex(ZeekAniIndex idx)
{
    if (m_currentAni == idx || idx == ZeekAniIndex_end)
        return;
    m_currentAni = idx;
    m_bodyArmature->getAnimation()->play(ZeekAniStr[idx]);
}

void Zeek::update(float delta)
{
    m_stateMachine->update(delta);
}

void Zeek::stopMove()
{
    setFaceTo(m_currentFaceTo);
}