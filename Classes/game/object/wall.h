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

#endif /* defined(__zeek__wall__) */
