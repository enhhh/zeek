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
:public Node
{
public:
    GameObject();
    
    ~GameObject();
    
    virtual bool init(tiledGid gid,Armature *bodyArmature,Vec2 coord);
    
    virtual bool move(Enum_Direction dir,GameObject *pusher = nullptr);
    
    virtual bool onCollided(GameObject *from);
    
public:
    
    bool        m_isMoveable;//物体是否可以移动
    bool        m_isDestructible;//是否可以被破坏
    Armature*     m_bodyArmature;
    Vec2        m_coord;
    tiledGid    m_tiledGid;//物体在地图中的GID
    bool        m_isMoving;//是否正在移动
};

#endif /* defined(__zeek__GameObject__) */
