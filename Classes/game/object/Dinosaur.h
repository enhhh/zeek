//
//  Dinosaur.h
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#ifndef __zeek__Dinosaur__
#define __zeek__Dinosaur__

#include "GameObject.h"

class Dinosaur
: public GameObject
{
public:
    static Dinosaur * create(Vec2 coord);
    
protected:
    
    Dinosaur();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    virtual void update(float delta) override;
    
    void playAnimation(bool state,Enum_Direction dir);
    
    bool checkCurrent();
    
    void turnLeft();
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr);
    
protected:
    
    Enum_Direction m_currentDirection;
    
    float m_restCountDown;
    
    bool m_currentState;//false = idle,true = move
    
    GameObject* m_readyKillPlayer;
};
#endif /* defined(__zeek__Dinosaur__) */
