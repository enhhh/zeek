//
//  Electrode.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__Electrode__
#define __zeek__Electrode__

#include "GameObject.h"
#include "AI/stateMachine/stateMachine.h"

class Electrode
: public GameObject
{
public:
    static Electrode * create(Vec2 coord);
    
    void startDestroyCountDown();
    
    void stopDestroyCountDown();
    
    void destroySelf();
    
protected:
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    Electrode();
    
    virtual void update(float delta) override;
    
public:
    StateMachine<Electrode> *m_stateMachine;
    
    bool m_isDestroying;
    float m_destroyCountDown;
protected:
    
};

#endif /* defined(__zeek__Electrode__) */
