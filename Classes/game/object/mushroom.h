//
//  mushroom.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__mushroom__
#define __zeek__mushroom__

#include "GameObject.h"

class Mushroom
: public GameObject
{
public:
    static Mushroom * create(Vec2 coord,bool poison);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;
    
    void switchPoison();
    
protected:
    
    Mushroom();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
public:
    bool m_isPoison;
};


#endif /* defined(__zeek__mushroom__) */
