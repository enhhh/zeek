//
//  dataStruct.h
//  zeek
//
//  Created by enh on 15/4/9.
//
//
#ifndef zeek_dataStruct_h
#define zeek_dataStruct_h

#include "cocos2d.h"
USING_NS_CC;

//config
#define GAME_MAP_OBJECT_LAYER "hazard"

#define ZEEK_MOVE_STEP_TIME 0.5f

#define ZEEK_REST_TIME 5.0f

#define ZEEK_TILED_OFFSET Vec2(18,18)

//enum
enum tiledGid
{
    tiledGid_begin,
    tiledGid_road,
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
    tiledGid_bomb,
    tiledGid_elected,
    tiledGid_oil,
    tiledGid_poisonFlower,
    tiledGid_magicEgg,
    tiledGid_dinosaur,
    tiledGid_evilEyes,
    tiledGid_bugApple,
    tiledGid_wall
};


//zeek动画列表
enum ZeekAniIndex
{
    walk_west,
    walk_east,
    walk_north,
    walk_south,
    idle_west,
    idle_east,
    idle_north,
    idle_south,
    poison,
    rest,
    ZeekAniIndex_end
};

extern const char* ZeekAniStr[];

//食人花动画列表
enum EaterAniIndex
{
    eat_apple_west,
    eat_apple_east,
    eat_apple_north,
    eat_apple_south,
    eat_zeek_west,
    eat_zeek_east,
    eat_zeek_north,
    eat_zeek_south,
    eater_opened,
    eater_open,
    eater_closed,
    eater_bugApple_west,
    eater_bugApple_east,
    eater_bugApple_north,
    eater_bugApple_south,
    eater_ani_end
};

enum DinosaurAniIndex
{
    dinosaur_idle_west,
    dinosaur_idle_south,
    dinosaur_idle_east,
    dinosaur_idle_north,
    dinosaur_walk_west,
    dinosaur_walk_south,
    dinosaur_walk_east,
    dinosaur_walk_north,
    DinosaurAniIndexEnd
};

extern const char* DinosaurAniStr[];
extern const char* EaterAniStr[];



enum Enum_Direction
{
    direction_west,
    direction_east,
    direction_north,
    direction_south,
    direction_end
};

extern const Vec2 DirectVector[];


#endif
