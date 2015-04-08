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
    
    if(ptr && ptr->init(tiledGid_zeed,nullptr,coordinate))
    {
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
}


bool Zeek::init(tiledGid gid,Sprite *bodySprite,Vec2 coord)
{
    //从缓存中读动画.
    Animation* zeekPoisonAni = AnimationCache::getInstance()->getAnimation("zeek_rest");
    auto ani = Animate::create(zeekPoisonAni);
    ani->retain();
    m_zeekAni[ZeekState::poison] = ani;
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("zeek_rest1.png");
    if(!bodySprite)
        m_bodySprite = Sprite::createWithSpriteFrame(frame);
    else
        m_bodySprite->setDisplayFrame(frame);
    m_bodySprite->runAction(RepeatForever::create(ani));
    return true;
}

void Zeek::moveTo(Zeek::moveDir dir)
{
    switch (dir) {
        case moveDir_East:
            
            break;
            
        default:
            break;
    }
}