//
//  Flower.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__Flower__
#define __zeek__Flower__

#include "preInclude.h"

class Flower
{
public:
    Flower(Sprite *texture,Vec2 coordinate,bool isPoison);
    
    ~Flower();
    
    void setPoison(bool bValue);
    
    bool isPoison();
    
protected:
    Sprite* m_texture;
    Vec2    m_coordinate;
    bool    m_isPoison;
};

#endif /* defined(__zeek__Flower__) */
