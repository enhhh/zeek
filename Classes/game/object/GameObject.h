//
//  GameObject.h
//  zeek
//
//  Created by enh on 15/4/8.
//
//

#ifndef __zeek__GameObject__
#define __zeek__GameObject__

#include "preInclude.h"

class GameObject
{
public:
    GameObject();
    
    ~GameObject();
    
    virtual bool init(tiledGid gid,Sprite *bodySprite,Vec2 coord);
    
public:
    
    bool        m_isMoveable;//物体是否可以移动
    bool        m_isDestructible;//是否可以被破坏
    Sprite*     m_bodySprite;
    Vec2        m_coord;
    tiledGid    m_tiledGid;//物体在地图中的GID
};

#endif /* defined(__zeek__GameObject__) */
