//
//  ElectrodeState.cpp
//  zeek
//
//  Created by enh on 15/4/19.
//
//

#include "ElectrodeState.h"
#include "GameMgr.h"
static ElectrodeState * s_pElectrodeState = nullptr;

ElectrodeState::ElectrodeState()
{
    
}

ElectrodeState * ElectrodeState::getInstance()
{
    if(!s_pElectrodeState)
        s_pElectrodeState = new ElectrodeState();
    return s_pElectrodeState;
}

void ElectrodeState::enter(Electrode *pOwner)
{
    
}

void ElectrodeState::execute(float delta, Electrode *pOwner)
{
    if(pOwner->m_destroyCountDown <= 0.0f)
    {
        pOwner->destroySelf();
        return;
    }
    
    
    auto coord = pOwner->m_coord;
    //上方判断
    Enum_Direction dir = Enum_Direction::direction_east;
    
    GameObject* obj = nullptr;
    do
    {
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,-1));
        if(obj && obj->m_tiledGid == tiledGid_electrode)
        {
            dir = direction_north;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(0,1));
        if(obj && obj->m_tiledGid == tiledGid_electrode)
        {
            dir = direction_south;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(1,0));
        if(obj && obj->m_tiledGid == tiledGid_electrode)
        {
            dir = direction_east;
            break;
        }
        obj = GameMgr::getInstance()->getGameObjectWithCoord(coord + Vec2(-1,0));
        if(obj && obj->m_tiledGid == tiledGid_electrode)
        {
            dir = direction_west;
            break;
        }
        obj = nullptr;
    }while (0);
    
    if(obj && pOwner->m_isDestroying == false)
    {
        pOwner->startDestroyCountDown();
        return;
    }
    

    
    if(!obj && pOwner->m_isDestroying == true)
    {
        pOwner->stopDestroyCountDown();
        return;
    }

}

void ElectrodeState::exit(Electrode *)
{
    
}