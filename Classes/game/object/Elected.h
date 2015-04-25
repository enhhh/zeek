//
//  Elected.h
//  zeek
//
//  Created by enh on 15/4/24.
//
//

#ifndef __zeek__Elected__
#define __zeek__Elected__

#include "GameObject.h"

class Elected
: public GameObject
{
public:
    static Elected * create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;
    
protected:
    
    Elected();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
};

#endif /* defined(__zeek__Elected__) */
