//
//  dataStruct.h
//  zeek
//
//  Created by enh on 15/4/9.
//
//
#ifndef zeek_dataStruct_h
#define zeek_dataStruct_h

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
    tiledGid_bomb
};

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

extern "C"
{
    const char* ZeekAniStr[ZeekAniIndex_end] =
    {
        "zeek_walk_west",
        "zeek_walk_east",
        "zeek_walk_north",
        "zeek_walk_south",
        "zeek_idle_west",
        "zeek_idle_east",
        "zeek_idle_south",
        "zeek_poison",
        "zeek_rest"
    };

}

enum Enum_Direction
{
    direction_west,
    direction_east,
    direction_north,
    direction_south
};


#endif
