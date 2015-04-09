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
public:
    static Zeek * create(Vec2 coordinate);
    
    void moveTo(const std::list<Vec2> & path);
    
    void death();
    
protected:
    virtual bool init(tiledGid gid,Sprite *bodySprite,Vec2 coord);
    
    Action* getMoveAction(Vec2 coord);
    
protected:
    std::map<ZeekState,Animate*> m_zeekAni;
    
    ZeekState   m_currentSate;//zeek当前的状态，用于控制动画
    
};

#endif /* defined(__zeek__Zeek__) */
