//
//  DinosaurState.cpp
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#include "DinosaurState.h"

static DinosaurIdleState * s_pDinosaurIdleState = nullptr;

DinosaurIdleState::DinosaurIdleState()
{
    
}

DinosaurIdleState*DinosaurIdleState::getInstance()
{
    if(!s_pDinosaurIdleState)
    {
        s_pDinosaurIdleState = new DinosaurIdleState();
    }
    return s_pDinosaurIdleState;
}

void DinosaurIdleState::enter(Dinosaur *pOwner)
{
    
}

void DinosaurIdleState::execute(float delta, Dinosaur *powner)
{
    
}

void DinosaurIdleState::exit(Dinosaur *powner)
{
    
}

//============================

static DinosaurMoveState * s_pDinosaurMoveState = nullptr;

DinosaurMoveState::DinosaurMoveState()
{
    
}

DinosaurMoveState*DinosaurMoveState::getInstance()
{
    if(!s_pDinosaurMoveState)
    {
        s_pDinosaurMoveState = new DinosaurMoveState();
    }
    return s_pDinosaurMoveState;
}

void DinosaurMoveState::enter(Dinosaur *pOwner)
{
    
}

void DinosaurMoveState::execute(float delta, Dinosaur *powner)
{
    
}

void DinosaurMoveState::exit(Dinosaur *powner)
{
    
}