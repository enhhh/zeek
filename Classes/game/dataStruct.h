//
//  dataStruct.h
//  zeek
//
//  Created by enh on 15/4/9.
//
//

#ifndef zeek_dataStruct_h
#define zeek_dataStruct_h


#define GAME_MAP_OBJECT_LAYER "hazard"
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

enum ZeekState
{
    walk_west,
    walk_east,
    walk_north,
    walk_south,
    poison,
    rest
};

enum moveDir
{
    moveDir_West,
    moveDir_East,
    moveDir_North,
    moveDir_South
};


#endif
