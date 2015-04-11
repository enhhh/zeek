//
//  ZeekState.cpp
//  zeek
//
//  Created by enh on 15/4/10.
//
//

#include "ZeekState.h"
static ZeekRestState* s_pZeekRestState = nullptr;

ZeekMoveState::ZeekMoveState()
{
    
}

void ZeekMoveState::enter(Zeek *pOwner)
{
    
}

void ZeekMoveState::execute(Zeek *pOwner)
{
    Vec2 curPos = pOwner->m_coord;
}