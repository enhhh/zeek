//
//  wall.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "wall.h"

Wall::Wall()
{
    m_isDestructible = false;
    m_isMoveable = false;
}

Wall* Wall::create(cocos2d::Vec2 coord)
{
    auto ptr = new Wall();
    if(ptr && ptr->init(tiledGid_wall, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

Oil::Oil()
{
    m_isDestructible = false;
    m_isMoveable = false;
}

Oil* Oil::create(cocos2d::Vec2 coord)
{
    auto ptr = new Oil();
    if(ptr && ptr->init(tiledGid_oil, nullptr, coord))
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}
