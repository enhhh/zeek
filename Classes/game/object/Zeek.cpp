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
{

}

Zeek::~Zeek()
{
	m_movePath.clear();
	delete m_stateMachine;
	for (auto &ani : m_zeekAni)
		ani.second->release();
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


bool Zeek::init(tiledGid gid,Sprite *bodySprite,Vec2 coord)
{
    GameObject::init(gid, bodySprite, coord);

	m_stateMachine = new StateMachine<Zeek>(this);
	m_stateMachine->changeState(ZeekRestState::getInstance());

    //从缓存中读动画.
	Animation* zeekAni = nullptr;
	Animate *animate = nullptr;
	zeekAni = AnimationCache::getInstance()->getAnimation("zeek_rest");
	animate = Animate::create(zeekAni);
	animate->retain();
	m_zeekAni[ZeekAniIndex::rest] = animate;

	zeekAni = AnimationCache::getInstance()->getAnimation("zeed_walk_east");
	animate = Animate::create(zeekAni);
	animate->retain();
	m_zeekAni[ZeekAniIndex::walk_east] = animate;

	zeekAni = AnimationCache::getInstance()->getAnimation("zeed_walk_north");
	animate = Animate::create(zeekAni);
	animate->retain();
	m_zeekAni[ZeekAniIndex::walk_north] = animate;

	zeekAni = AnimationCache::getInstance()->getAnimation("zeed_walk_south");
	animate = Animate::create(zeekAni);
	animate->retain();
	m_zeekAni[ZeekAniIndex::walk_south] = animate;
    
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_south1.png");
	if (!m_bodySprite)
    {
        m_bodySprite = Sprite::createWithSpriteFrame(frame);
		m_bodySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        this->addChild(m_bodySprite);
    }
	scheduleUpdate();
    return true;
}

void Zeek::moveTo(Enum_Direction dir)
{
	m_isMoving = true;

	auto endcall = [=](){ m_isMoving = false; };

	auto endAction = CallFunc::create(endcall);

	switch (dir)
	{
	case direction_west:
		this->runAction(Sequence::create(
			MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord += Vec2(1, 0)))
			,endAction,nullptr));
		break;
	case direction_east:
		this->runAction(Sequence::create(
			MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord += Vec2(-1, 0)))
			, endAction, nullptr));
		break;
	case direction_north:
		this->runAction(Sequence::create(
			MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord += Vec2(0, -1)))
			, endAction, nullptr));
		break;
	case direction_south:
		this->runAction(Sequence::create(
			MoveTo::create(0.5f, GameMgr::getInstance()->getPositionWithCoord(m_coord += Vec2(0, 1)))
			, endAction, nullptr));
		break;
	default:
		break;
	}
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
	m_bodySprite->stopAllActions();
	switch (dir)
	{
	case direction_west:
		m_bodySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_east1.png"));
		m_bodySprite->setScaleX(-1);
		break;
	case direction_east:
		m_bodySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_east1.png"));
		break;
	case direction_north:
		m_bodySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_north1.png"));
		break;
	case direction_south:
		m_bodySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_south1.png"));
		break;
	default:
		m_bodySprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zeed_walk_south1.png"));
		break;
	}
}

void Zeek::playAnimationWithIndex(ZeekAniIndex idx, bool repeat)
{
	if (m_currentAni == idx || idx == ZeekAniIndex_end)
		return;
	m_currentAni = idx;

	if (repeat)
		m_bodySprite->runAction(RepeatForever::create(m_zeekAni[idx]));
	else
		m_bodySprite->runAction(Sequence::create(m_zeekAni[idx], CallFunc::create([=](){m_currentAni = ZeekAniIndex_end; })));
}

void Zeek::update(float delta)
{
	m_stateMachine->update(delta);
}
