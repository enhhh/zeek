//
//  Flower.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Flower__
#define __zeek__Flower__

#include "GameObject.h"

class Flower
:public GameObject
{
public:
    static Flower *create(Vec2 );
};

#endif /* defined(__zeek__Flower__) */
