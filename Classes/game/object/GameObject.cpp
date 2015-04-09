//
//  GameObject.cpp
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#include "GameObject.h"

GameObject::GameObject()
: m_bodySprite(nullptr)
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

bool GameObject::init(tiledGid gid, cocos2d::Sprite *bodySprite, cocos2d::Vec2 coord)
{
    m_bodySprite = bodySprite;
    m_tiledGid = gid;
    m_coord = coord;
    if(m_bodySprite)
        this->addChild(m_bodySprite);
    return true;
}