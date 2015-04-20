//
//  Bomb.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__Bomb__
#define __zeek__Bomb__

#include "GameObject.h"


class Bomb
: public GameObject
{
public:
    static Bomb* create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr);
    
protected:
    Bomb();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    virtual void update(float delta) override;
protected:
    bool m_isDestroying;
    float m_destroyCountDown;
};
#endif /* defined(__zeek__Bomb__) */
