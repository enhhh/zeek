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

class Zeek
: public Sprite
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
    
    
public:
    static Zeek * create(Vec2 );
    
    void walkToPosition(Vec2 tmxCoord);
    
    void death();
    
protected:
    virtual bool init() override;
    
protected:
    std::map<ZeekState,Animate*> m_zeekAni;
    
    Vect    m_Coordinate;
    
};

#endif /* defined(__zeek__Zeek__) */
