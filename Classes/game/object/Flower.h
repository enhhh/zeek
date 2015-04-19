//
//  Flower.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Flower__
#define __zeek__Flower__

#include "GameObject.h"

class Flower
:public GameObject
{
public:
    static Flower *create(Vec2 coord,bool poison);
    
    void switchPoison();
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;

protected:
    Flower();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
protected:
    bool m_isPoison;
};

#endif /* defined(__zeek__Flower__) */
