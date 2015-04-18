//
//  Apple.h
//  zeek
//
//  Created by enh on 15/4/18.
//
//

#ifndef __zeek__Apple__
#define __zeek__Apple__

#include "GameObject.h"

class Apple
: public GameObject
{
public:
    static Apple * create(Vec2 coord,bool hasBug);
    
protected:
    Apple();
    
    ~Apple();
    
    virtual bool init(tiledGid gid, Armature *bodyArmature, cocos2d::Vec2 coord);
    
    
    
protected:
    
    bool m_hasBug;
};

#endif /* defined(__zeek__Apple__) */
