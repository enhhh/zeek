//
//  Zeek.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Zeek__
#define __zeek__Zeek__

#include "GameObject.h"
#include  "AI/stateMachine/stateMachine.h"

class Zeek
: public GameObject
{
public:
    
    static Zeek * create(Vec2 coordinate);
    
    void playAnimationWithIndex(ZeekAniIndex idx);
    
	void moveTo(Enum_Direction dir);
    
    Vec2 getNextMoveCoord();

	bool isMoving(){ return m_isMoving; }
    
	StateMachine<Zeek> * getStateMachine(){ return m_stateMachine; }

	int getPathStep(){ return m_movePath.size(); }

	void setFaceTo(Enum_Direction dir);//stop all body Animation

	void setMovePath(const std::list<Vec2> &path){ m_movePath = path; }
    
    void stopMove();

protected:
    
    Zeek();
    
    ~Zeek();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    Action* getMoveAction(Vec2 coord);
    
    virtual void update(float delta) override;
    
protected:
    
    StateMachine<Zeek> * m_stateMachine;
    
    std::list<Vec2> m_movePath;
    
    ZeekAniIndex m_currentAni;
    
	bool m_isMoving;
    Enum_Direction m_currentFaceTo;
    
};

#endif /* defined(__zeek__Zeek__) */
