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
    
    enum tiledGid
    {
        tiledGid_begin,
        tiledGid_zeed,
        tiledGid_apple,
        tiledGid_ball,
        tiledGid_openEater,
        tiledGid_closeEater,
        tiledGid_key,
        tiledGid_door,
        tiledGid_healthyFlower,
        tiledGid_healthyMushroom,
        tiledGid_electrode,
        tiledGid_poisonousMushroom,
        tiledGid_chest,
        tiledGid_bomb
    };
    
    
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
