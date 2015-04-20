//
//  magicEgg.h
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#ifndef __zeek__magicEgg__
#define __zeek__magicEgg__

#include "GameObject.h"

class MagicEgg
: public GameObject
{
public:
    static MagicEgg*create(Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr) override;
    
protected:
    
    MagicEgg();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    void switchPoison();
};
#endif /* defined(__zeek__magicEgg__) */
