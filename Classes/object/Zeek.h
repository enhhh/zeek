//
//  Zeek.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Zeek__
#define __zeek__Zeek__

#include "preInclude.h"
#include "GameObject.h"

class Zeek
: public GameObject
{
    enum ZeekState
    {
        walk_west,
        walk_east,
        walk_north,
        walk_south,
        poison,
        rest
    };
    
    enum moveDir
    {
        moveDir_West,
        moveDir_East,
        moveDir_North,
        moveDir_South
    };
    
    
    
public:
    static Zeek * create(Vec2 coordinate);
    
    void moveTo(moveDir dir);
    
    void death();
    
protected:
    virtual bool init(tiledGid gid,Sprite *bodySprite,Vec2 coord);
    
protected:
    std::map<ZeekState,Animate*> m_zeekAni;
    
};

#endif /* defined(__zeek__Zeek__) */
