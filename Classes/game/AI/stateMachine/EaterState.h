//
//  EaterState.h
//  zeek
//
//  Created by enh on 15/4/15.
//
//

#ifndef __zeek__EaterState__
#define __zeek__EaterState__

#include "state.h"
#include "object/Eater.h"

class EaterOpenState
: public State<Eater>
{
public:
    static EaterOpenState* getInstance();
    
    virtual void enter(Eater *);
    
    virtual void execute(float delta,Eater *);
    
    virtual void exit(Eater *);
    
protected:
    EaterOpenState();
    
};

class EaterClosedState
: public State<Eater>
{
public:
    static EaterClosedState* getInstance();
    
    virtual void enter(Eater *);
    
    virtual void execute(float delta,Eater *);
    
    virtual void exit(Eater *);
    
protected:
    EaterClosedState();
};

class EaterChewState
: public State<Eater>
{
public:
    
    static EaterChewState* getInstance();
    
    virtual void enter(Eater *);
    
    virtual void execute(float delta,Eater *);
    
    virtual void exit(Eater *);
    
protected:
    
    EaterChewState();
};

class EaterOpenningState
: public State<Eater>
{
public:
    static EaterOpenningState * getInstance();
    
    virtual void enter(Eater *);
    
    virtual void execute(float delta,Eater *);
    
    virtual void exit(Eater *);
protected:
    EaterOpenningState();
};
#endif /* defined(__zeek__EaterState__) */
