//
//  ZeekState.cpp
//  zeek
//
//  Created by enh on 15/4/10.
//
//

#include "ZeekState.h"

static ZeekRestState* s_pZeekRestState = nullptr;

ZeekRestState::ZeekRestState()
{

}

ZeekRestState* ZeekRestState::getInstance()
{
	if (!s_pZeekRestState)
		s_pZeekRestState = new ZeekRestState();
	return s_pZeekRestState;
}

void ZeekRestState::enter(Zeek *pOwner)
{
	m_noOperatorTime = 0;
}

void ZeekRestState::execute(float delta,Zeek *pOwner)
{
	m_noOperatorTime += delta;
	if (m_noOperatorTime >= ZEEK_REST_TIME)
		pOwner->playAnimationWithIndex(ZeekAniIndex::rest, true);
	if (pOwner->getPathStep() > 0)
		pOwner->getStateMachine()->changeState(ZeekMoveState::getInstance());
}

void ZeekRestState::exit(Zeek *pOwner)
{

}

static ZeekMoveState* s_pZeekMoveState = nullptr;
ZeekMoveState::ZeekMoveState()
{
    
}

ZeekMoveState * ZeekMoveState::getInstance()
{
	if (!s_pZeekMoveState)
		s_pZeekMoveState = new ZeekMoveState();
	return s_pZeekMoveState;
}

void ZeekMoveState::enter(Zeek *pOwner)
{
    
}

void ZeekMoveState::execute(float delta,Zeek *pOwner)
{
	if (pOwner->isMoving())
		return;

    Vec2 curPos = pOwner->m_coord;
	Vec2 nextPos = pOwner->getNextMoveCoord();

	if (curPos == nextPos)
		pOwner->getStateMachine()->changeState(ZeekRestState::getInstance());

	Vec2 dir = curPos - nextPos;
	ZeekAniIndex nextAni;
	if (dir.x == -1)
	{
		pOwner->moveTo(direction_west);
		nextAni = ZeekAniIndex::walk_west;
	}
	else if (dir.y == -1)
	{
		nextAni = ZeekAniIndex::walk_south;
		pOwner->moveTo(direction_south);
	}
	else if (dir.x == 1)
	{
		nextAni = ZeekAniIndex::walk_east;
		pOwner->moveTo(direction_east);
	}
	else if (dir.y == 1)
	{
		nextAni = ZeekAniIndex::walk_north;
		pOwner->moveTo(direction_north);
	}
	else
	{
		log("walk error : m_currentPos = (%f,%f), destPos = (%f,%f)", curPos.x, curPos.y, nextPos.x, nextPos.y);
		pOwner->getStateMachine()->changeState(ZeekRestState::getInstance());
	}

}

void ZeekMoveState::exit(Zeek *pOwner)
{
	
}