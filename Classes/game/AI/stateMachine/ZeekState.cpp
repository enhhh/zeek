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
		pOwner->playAnimationWithIndex(ZeekAniIndex::rest);
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
    {
		pOwner->getStateMachine()->changeState(ZeekRestState::getInstance());
        return;
    }

	Vec2 dir = nextPos - curPos;
	ZeekAniIndex nextAni = ZeekAniIndex_end;
	if (dir.x == -1)
	{
		pOwner->move(direction_west);
		nextAni = ZeekAniIndex::walk_west;
	}
	else if (dir.y == 1)
	{
		nextAni = ZeekAniIndex::walk_south;
		pOwner->move(direction_south);
	}
	else if (dir.x == 1)
	{
		nextAni = ZeekAniIndex::walk_east;
		pOwner->move(direction_east);
	}
	else if (dir.y == -1)
	{
		nextAni = ZeekAniIndex::walk_north;
		pOwner->move(direction_north);
	}
	else
	{
		log("walk error : m_currentPos = (%f,%f), destPos = (%f,%f)", curPos.x, curPos.y, nextPos.x, nextPos.y);
		pOwner->getStateMachine()->changeState(ZeekRestState::getInstance());
	}
    pOwner->playAnimationWithIndex(nextAni);
}

void ZeekMoveState::exit(Zeek *pOwner)
{
    pOwner->stopMove();
}