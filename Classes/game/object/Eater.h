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
    static Eater* create(Vec2 coord,bool state);
    
    void playAnimationWithIndex(EaterAniIndex idx);
    
protected:
    
    Eater();
    
    ~Eater();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    virtual void update(float delta);
    
protected:

    
    EaterAniIndex m_currentAni;
    
    bool m_currentState;//true 打开状态
public:
    StateMachine<Eater> * m_stateMachine;
    bool m_isPlayingAnimation;//eater通过动画播放时间来决定状态变更
};


#endif /* defined(__zeek__Eater__) */
