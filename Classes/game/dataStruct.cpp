//
//  dataStruct.cpp
//  zeek
//
//  Created by enh on 15/4/14.
//
//

#include "dataStruct.h"


const char* ZeekAniStr[ZeekAniIndex_end] =
{
    "zeek_walk_west",
    "zeek_walk_east",
    "zeek_walk_north",
    "zeek_walk_south",
    "zeek_idle_west",
    "zeek_idle_east",
    "zeek_idle_north",
    "zeek_idle_south",
    "zeek_poison",
    "zeek_rest"
};


const char *EaterAniStr[eater_ani_end] =
{
    "eatApple_west",
    "eatApple_east",
    "eatApple_north",
    "eatApple_south",
    "eatZeek_west",
    "eatZeek_east",
    "eatZeek_north",
    "eatZeek_south",
    "opened",
    "open",
    "closed",
    "eatBugApple_west",
    "eatBugApple_east",
    "eatBugApple_north",
    "eatBugApple_south"
};

const char *DinosaurAniStr[DinosaurAniIndexEnd] =
{
    "IdleLeft",
    "IdleDown",
    "IdleRight",
    "IdleUp",
    "MoveLeft",
    "MoveDown",
    "MoveRight",
    "MoveUp"
};

const Vec2 DirectVector[direction_end]=
{
    Vec2(-1,0),
    Vec2(1,0),
    Vec2(0,-1),
    Vec2(0,1)
};
