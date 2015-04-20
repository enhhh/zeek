//
//  wall.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__wall__
#define __zeek__wall__

#include "GameObject.h"

class Wall
: public GameObject
{
public:
    static Wall *create(Vec2 coord);
    
    
protected:
    Wall();
    
};

class Oil
: public GameObject
{
public:
    static Oil *create(Vec2 coord);
    
protected:
    Oil();
    
//    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
};

#endif /* defined(__zeek__wall__) */
