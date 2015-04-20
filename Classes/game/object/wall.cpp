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

//bool Oil::init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord)
//{
//    if(!GameObject::init(gid, bodyArmature, coord))
//        return false;
//    
//    if(!bodyArmature)
//    {
//        m_bodyArmature = Armature::create("oil");
//        if(m_bodyArmature)
//        {
//            m_bodyArmature->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//            this->addChild(m_bodyArmature);
//            m_bodyArmature->getAnimation()->play("oil");
//        }
//    }
//    return true;
//}
