//
//  GameMgr.cpp
//  zeek
//
//  Created by enh on 15/4/9.
//
//
#include "AI/AStar.h"
#include "object/Zeek.h"
#include "GameMgr.h"


static GameMgr * s_pGameMgr = nullptr;


GameMgr::GameMgr()
: m_zeek(nullptr)
, m_gameMap(nullptr)
, m_sourceInited(false)
, m_gameScene(nullptr)
{
    
}

GameMgr::~GameMgr()
{
    clearGameScene();
}

GameMgr * GameMgr::getInstance()
{
    if(!s_pGameMgr)
        s_pGameMgr = new GameMgr();
    return s_pGameMgr;
}

void GameMgr::setGameScene(cocos2d::Scene *scene)
{
    if(m_gameScene)
        clearGameScene();
    
    m_gameScene = scene;
}


void GameMgr::clearGameScene(bool clearCache)
{
    for (auto object : m_objects) {
        delete object;
    }
    m_objects.clear();
    m_zeek = nullptr;//主角在m_objects里一起被释放
    if(m_gameMap)
        m_gameMap->removeFromParent();
    m_gameScene = nullptr;
    if(clearCache)
    {
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("sprites.plist");
        ArmatureDataManager::getInstance()->destroyInstance();
        m_sourceInited = false;
    }
}



bool GameMgr::loadGame(int level)
{
    if(!m_sourceInited)
        preloadSource();
    
    if(m_gameMap)
        clearGameScene(false);
    if (!level) {
        //测试信息
        m_gameMap = TMXTiledMap::create("test.tmx");
    }
    else
    {
        
    }
    
    if(!m_gameMap)
        return false;
    
    
    if(! m_gameScene)
    {
        log("游戏场景未初始化");
        return false;
    }
    m_gameScene->addChild(m_gameMap);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameMgr::onMapTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameMgr::onMapTouchMove,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameMgr::onMapTouchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_gameMap);
    
    initGameObject();

    //PathFind::getInstance()->AStarSearch(m_gameMap,2,10,11,4);
    return true;
    
    return true;
}


//游戏资源管理

void GameMgr::preloadSource()
{
    if (m_sourceInited)
        return;
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/zeek.ExportJson");
    
    m_sourceInited = true;
}

//=========================
//
//运行时对象管理
//
//========================

void GameMgr::initGameObject()
{
   if(!m_gameMap)
   {
       log("game map not loaded");
       return;
   }
    auto objectLayer = m_gameMap->getLayer(GAME_MAP_OBJECT_LAYER);
    if(!objectLayer)
    {
        log("game map not contain object layer");
        return;
    }
    
    auto size = objectLayer->getLayerSize();
    
    for(int i = 0; i < size.width; i++)
    {
        for(int j = 0 ; j < size.height;j++)
        {
            if(objectLayer->getTileGIDAt(Vec2(i,j)) == tiledGid_zeed)
            {
                objectLayer->getTileAt(Vec2(i,j))->removeFromParentAndCleanup(true);
                if(!m_zeek)
                {
                    m_zeek = Zeek::create(Vec2(i,j)); //创建主角
                    pushGameObject(m_zeek);//是否需要??
                    
                    m_gameScene->addChild(m_zeek);
                }
                auto pos = objectLayer->convertToWorldSpace(objectLayer->getPositionAt(Vect(i,j)));
                m_zeek->setPosition(pos);
            }
        }
    }

    
}

GameObject* GameMgr::getGameObjectWithCoord(cocos2d::Vec2 coord)
{
    for(auto object : m_objects)
    {
        if(object->m_coord == coord)
            return object;
    }
    
    return nullptr;
}

void GameMgr::pushGameObject(GameObject *obj)
{
    m_objects.push_back(obj);
}

bool GameMgr::removeGameObjectFromMap(GameObject *obj)
{
    for (auto object = m_objects.begin();object != m_objects.end();object++)
    {
        if(*object == obj)
        {
            obj->removeFromParent();
            m_objects.erase(object);
            return true;
        }
    }
    return false;
}

bool GameMgr::removeGameObjectFromMap(Vec2 coord)
{
    for (auto object = m_objects.begin();object != m_objects.end();object++)
    {
        if((*object)->m_coord == coord)
        {
            (*object)->removeFromParent();
            m_objects.erase(object);
            return true;
        }
    }
    return false;
}


//事件管理

bool GameMgr::onMapTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 locationInNode = m_gameMap->convertToNodeSpace(touch->getLocation());
    Size s = m_gameMap->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        //this->setColor(Color3B::RED);
        return true;
    }
    return false;
}

void GameMgr::onMapTouchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void GameMgr::onMapTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 locationInNode = m_gameMap->convertToNodeSpace(touch->getLocation());
    int x = locationInNode.x / m_gameMap->getTileSize().width;
    int y = m_gameMap->getMapSize().height - locationInNode.y / m_gameMap->getTileSize().height;

	bool result = PathFind::getInstance()->AStarSearch(m_gameMap, m_zeek->m_coord.x, m_zeek->m_coord.y, x, y);
	if (result)
		m_zeek->setMovePath(PathFind::getInstance()->astarPathList);
}


//地图相关
Vec2 GameMgr::getPositionWithCoord(cocos2d::Vec2 coord)
{
    if(m_gameMap)
    {
        auto objectLayer = m_gameMap->getLayer(GAME_MAP_OBJECT_LAYER);
        if(objectLayer)
			return objectLayer->getPositionAt(coord) + ZEEK_TILED_OFFSET;
    }
    return Vec2(-1,-1);
}