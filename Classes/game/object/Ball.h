//
//  Ball.h
//  zeek
//
//  Created by enh on 15/4/20.
//
//

#ifndef __zeek__Ball__
#define __zeek__Ball__

#include "GameObject.h"

class Ball
: public GameObject
{
public:
    
    static Ball *create(Vec2 coord);
    
protected:
    Ball();
    
    bool init(tiledGid gid, cocostudio::Armature *bodyArmature, cocos2d::Vec2 coord);
};

#endif /* defined(__zeek__Ball__) */
