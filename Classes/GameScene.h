//
//  GameScene.h
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#ifndef __zeek__GameScene__
#define __zeek__GameScene__
#include "preInclude.h"
#include "object/Zeek.h"
#include "object/GameObjectMgr.h"
class GameScene
: public Scene
{
public:

    
    static GameScene*create();
    
    bool loadGameMap(const std::string& fileName);
protected:
    
    GameScene();
    
    ~GameScene();
    
    bool parseGameMap(TMXLayer *objectLayer);
    
    void initAnimation();
    
    bool onMapTouchBegan(Touch *touch,Event *event);
    
    void  onMapTouchMove(Touch*touch,Event *event);
    
    void onMapTouchEnd(Touch*touch,Event*event);
    
    const GameObjectMgr& getGameObjectMgr()
    {
        return m_gameObjectMgr;
    }
    
protected:
    TMXTiledMap*    m_gameMap;
    TMXLayer*       m_objectLayer;
    
    Zeek*       m_zeek;
    
    GameObjectMgr m_gameObjectMgr;
    
};


#endif /* defined(__zeek__GameScene__) */
