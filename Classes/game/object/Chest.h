//
//  Chest.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__Chest__
#define __zeek__Chest__

#include "GameObject.h"

class Chest
: public GameObject
{
public:
    static Chest * create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;
    
protected:
    
    Chest();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
};
#endif /* defined(__zeek__Chest__) */
