//
//  Eater.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Eater__
#define __zeek__Eater__

#include "GameObject.h"
#include "AI/stateMachine/stateMachine.h"

class Eater
: public GameObject
{
public:
    static Eater* create(Vec2 coord);
    
protected:
    
    Eater();
    
    ~Eater();
    
    StateMachine<Eater> * m_stateMachine;
    
    EaterAniIndex m_currentAni;
};


#endif /* defined(__zeek__Eater__) */
