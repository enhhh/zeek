//
//  ZeekState.h
//  zeek
//
//  Created by enh on 15/4/10.
//
//

#ifndef __zeek__ZeekState__
#define __zeek__ZeekState__

#include "state.h"
#include "object/Zeek.h"
class ZeekRestState
: public State<Zeek>
{
public:
    static ZeekRestState* getInstance();
    
    virtual void enter(Zeek *);
    
    virtual void execute(Zeek *);
    
    virtual void exit(Zeek *);
    
protected:
    ZeekRestState();
};

class ZeekMoveState
: public State<Zeek>
{
public:
    static ZeekMoveState *getInstance();
    
    virtual void enter(Zeek *);
    
    virtual void execute(Zeek *);
    
    virtual void exit(Zeek *);
    
protected:
    
    ZeekMoveState();
};



#endif /* defined(__zeek__ZeekState__) */
