//
//  GameObject.cpp
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#include "GameObject.h"

GameObject::GameObject()
: m_bodyArmature(nullptr)
, m_isMoveable(false)
, m_isDestructible(false)
, m_tiledGid(tiledGid_begin)
, m_coord(Vec2::ZERO)
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