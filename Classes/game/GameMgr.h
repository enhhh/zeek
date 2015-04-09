//
//  GameMgr.h
//  zeek
//
//  Created by enh on 15/4/9.
//
//

#ifndef __zeek__GameMgr__
#define __zeek__GameMgr__

#include "preInclude.h"
#include "object/GameObject.h"

class Zeek;
class GameMgr
{
public:
    static GameMgr * getInstance();
    
    bool loadGame(int level = 0);//level 0 is testScene
    
    void clearGameScene(bool clearCache = true);//切换场景后清空游戏信息
    
    void setGameScene(Scene *scene);
    //资源管理
    
    bool isSourceInited(){return m_sourceInited;}
    
    void preloadSource();
    
    ///运行时对象管理
    
    void initGameObject();
    
    GameObject* getGameObjectWithCoord(Vec2 coord);
    
    void pushGameObject(GameObject* obj);
    
    bool removeGameObjectFromMap(GameObject *obj);
    
    bool removeGameObjectFromMap(Vec2 coord);
    
    //地图相关
    
    Vec2 getPositionWithCoord(Vec2 coord);
    
protected:
    GameMgr();
    
    ~GameMgr();
    
    //事件管理
    bool onMapTouchBegan(Touch *touch,Event *event);
    
    void onMapTouchMove(Touch*touch,Event *event);
    
    void onMapTouchEnd(Touch*touch,Event*event);
    
    
protected:
    std::vector<GameObject*> m_objects;
    
    bool m_sourceInited; //
    
    TMXTiledMap*        m_gameMap;
    Zeek*               m_zeek;
    Scene*              m_gameScene;
};

#endif /* defined(__zeek__GameMgr__) */
