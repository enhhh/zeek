//
//  Zeek.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "Zeek.h"
#include "game/GameMgr.h"

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
    GameObject::init(gid, bodySprite, coord);
    //从缓存中读动画.
    Animation* zeekPoisonAni = AnimationCache::getInstance()->getAnimation("zeek_rest");
    auto ani = Animate::create(zeekPoisonAni);
    ani->retain();
    m_zeekAni[ZeekState::poison] = ani;
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("zeek_rest1.png");
    if(!bodySprite)
    {
        m_bodySprite = Sprite::createWithSpriteFrame(frame);
        this->addChild(m_bodySprite);
    }
    
    else
        m_bodySprite->setSpriteFrame(frame);
    m_bodySprite->runAction(RepeatForever::create(ani));
    return true;
}

void Zeek::moveTo(const std::list<Vec2> &path)
{
	if (path.empty())
		return;
	auto pt = path;
	auto action = getMoveAction(*pt.begin());
	pt.pop_front();
	auto endCall = [=](){
		if (pt.empty())
			return;
		auto act = getMoveAction(*pt.begin());
		this->runAction(Sequence::create(act, CallFunc::create(endCall), nullptr));
	};
}

Action* Zeek::getMoveAction(Vec2 coord)
{
    Vec2 dest = GameMgr::getInstance()->getPositionWithCoord(coord);
    
    //获取运动方向
    Vec2 dir = coord - m_coord;
    ZeekState nextSate;
    if(dir.x == -1) // move west
        nextSate = ZeekState::walk_west;
    else if(dir.y == -1)
        nextSate = ZeekState::walk_south;
    else if(dir.x == 1)
        nextSate = ZeekState::walk_east;
    else if(dir.y == 1)
        nextSate = ZeekState::walk_north;
    else
    {
        log("walk error : m_currentPos = (%f,%f), destPos = (%f,%f)",m_coord.x,m_coord.y,coord.x,coord.y);
        return nullptr;
    }
    CallFunc* fun = nullptr;
    
    if(m_currentSate != nextSate)
    {
        auto lamda = [=](){
            m_bodySprite->runAction(RepeatForever::create(m_zeekAni[nextSate]));
        };
        fun = CallFunc::create(lamda);
    }
	if (fun)
	{
		return Spawn::createWithTwoActions(MoveTo::create(0.5f, dest), fun);
	}
	else
		return MoveTo::create(0.f, dest);
}