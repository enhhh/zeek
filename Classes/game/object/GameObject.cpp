//
//  GameObject.cpp
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#include "GameObject.h"
#include "GameMgr.h"
GameObject::GameObject()
: m_bodyArmature(nullptr)
, m_isMoveable(false)
, m_isDestructible(false)
, m_tiledGid(tiledGid_begin)
, m_coord(Vec2::ZERO)
, m_isMoving(true)
{
    this->setContentSize(Size::ZERO); //设置一个点用于播放非动画类的动作
}

GameObject::~GameObject()
{
}

bool GameObject::init(tiledGid gid, Armature *bodyArmature, cocos2d::Vec2 coord)
{
    m_bodyArmature = bodyArmature;
    m_tiledGid = gid;
    m_coord = coord;
    if(m_bodyArmature)
        this->addChild(m_bodyArmature);
    return true;
}

bool GameObject::move(Enum_Direction dir,GameObject *pusher)
{
    if(!m_isMoveable)
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
    m_isMoving = true;
    m_coord = targetVec;
    auto endcall = [=](){ m_isMoving = false;};
    this->runAction(Sequence::create(
                                     MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(targetVec))
                                     , CallFunc::create(endcall), nullptr));

    return true;
}

bool GameObject::onCollided(GameObject *from)
{
    return true;
}