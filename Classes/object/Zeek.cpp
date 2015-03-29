//
//  Zeek.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "Zeek.h"

#define ZEEK_SPEED 1

Zeek * Zeek::create(Vec2 coordinate)
{
    auto ptr = new Zeek();
    
    if(ptr && ptr->init())
    {
        ptr->m_Coordinate = coordinate;
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
}


bool Zeek::init()
{
    if(!cocos2d::Sprite::init())
        return false;
    
    //从缓存中读动画.
    Animation* zeekPoisonAni = AnimationCache::getInstance()->getAnimation("zeek_rest");
    auto ani = Animate::create(zeekPoisonAni);
    ani->retain();
    m_zeekAni[ZeekState::poison] = ani;
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("zeek_rest1.png");
    this->setDisplayFrame(frame);
    this->runAction(RepeatForever::create(ani));
    return true;
}

void Zeek::walkToPosition(Vec2 tmxCoord)
{
    auto moveTo = MoveTo::create(3, tmxCoord);
}