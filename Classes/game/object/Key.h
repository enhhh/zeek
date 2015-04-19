//
//  Key.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__Key__
#define __zeek__Key__

#include "GameObject.h"

class Key
: public GameObject
{
public:
    static Key * create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;
    
protected:
    
    Key();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
};
#endif /* defined(__zeek__Key__) */
