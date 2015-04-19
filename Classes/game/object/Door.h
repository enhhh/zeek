//
//  Door.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__Door__
#define __zeek__Door__

#include "GameObject.h"

class Door
: public GameObject
{
public:
    static Door * create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr);
    
protected:
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    Door();

};

#endif /* defined(__zeek__Door__) */
