//
//  DinosaurState.h
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#ifndef __zeek__DinosaurState__
#define __zeek__DinosaurState__

#include "state.h"
#include "object/Dinosaur.h"

class DinosaurMoveState
: public State<Dinosaur>
{
public:
    static DinosaurMoveState* getInstance();
    
    virtual void enter(Dinosaur *);
    
    virtual void execute(float delta,Dinosaur *);
    
    virtual void exit(Dinosaur *);
    
protected:
    DinosaurMoveState();
};

class DinosaurIdleState
: public State<Dinosaur>
{
    static DinosaurIdleState* getInstance();
    
    virtual void enter(Dinosaur *);
    
    virtual void execute(float delta,Dinosaur *);
    
    virtual void exit(Dinosaur *);
protected:
    DinosaurIdleState();
};

#endif /* defined(__zeek__DinosaurState__) */
