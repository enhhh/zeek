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
#include "object/Eater.h"
#include "object/Apple.h"
#include "object/wall.h"
#include "object/Flower.h"
#include "object/Key.h"
#include "object/Door.h"
#include "object/Electrode.h"
#include "object/Chest.h"
#include "object/mushroom.h"
#include "object/magicEgg.h"
#include "object/Ball.h"
#include "object/Bomb.h"

#include <stdio.h>

static GameMgr * s_pGameMgr = nullptr;


GameMgr::GameMgr()
: m_zeek(nullptr)
, m_gameMap(nullptr)
, m_sourceInited(false)
, m_gameScene(nullptr)
, m_currentLevel(0)
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
        object->removeFromParentAndCleanup(true);
    }
    m_objects.clear();
    m_zeek = nullptr;//主角在m_objects里一起被释放
    if(m_gameMap)
    {
        m_gameMap->removeFromParent();
        m_gameMap = nullptr;
    }
    
    
    if(clearCache)
    {
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("sprites.plist");
        ArmatureDataManager::getInstance()->destroyInstance();
        m_sourceInited = false;
        m_gameScene = nullptr;
    }
}


void GameMgr::gotoNextLevel()
{
    clearGameScene(false);
    loadGame(m_currentLevel+1);
}

void GameMgr::restartCurrentLevel()
{
    clearGameScene(false);
    loadGame(m_currentLevel);
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
        char path[255] = {0};
        sprintf(path,"level/Level%d.tmx", level);
        m_gameMap = TMXTiledMap::create(path);
    }
    m_currentLevel = level;
    
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
	ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/eater.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/apple.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/ball.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/key.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/flower.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/electrode.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/door.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/chest.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/mushroom.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/magicEgg.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/oil.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/bomb.ExportJson");
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
			tiledGid objGid = (tiledGid)objectLayer->getTileGIDAt(Vec2(i, j));
            if(!objGid)
                continue;
            GameObject *object = nullptr;
            switch (objGid) {
                case tiledGid_apple:
                    object = Apple::create(Vec2(i,j),false);
                    break;
                case tiledGid_bugApple:
                    object = Apple::create(Vec2(i, j),true);
                    break;
                case tiledGid_zeed:
                     m_zeek = Zeek::create(Vec2(i,j));
                    object = m_zeek;
                    break;
                case tiledGid_openEater:
                    object = Eater::create(Vec2(i,j), true);
                    break;
                case tiledGid_closeEater:
                    object = Eater::create(Vec2(i,j), false);
                    break;
                case tiledGid_poisonFlower:
                    object = Flower::create(Vec2(i,j), true);
                    break;
                case tiledGid_healthyFlower:
                    object = Flower::create(Vec2(i,j), false);
                    break;
                case tiledGid_key:
                    object = Key::create(Vec2(i,j));
                    break;
                case tiledGid_door:
                    object = Door::create(Vec2(i,j));
                    break;
                case tiledGid_electrode:
                    object = Electrode::create(Vec2(i,j));
                    break;
                case tiledGid_chest:
                    object = Chest::create(Vec2(i,j));
                    break;
                case tiledGid_healthyMushroom:
                    object = Mushroom::create(Vec2(i,j), false);
                    break;
                case tiledGid_poisonousMushroom:
                    object = Mushroom::create(Vec2(i,j), true);
                    break;
                case tiledGid_magicEgg:
                    object = MagicEgg::create(Vec2(i,j));
                    break;
                case tiledGid_ball:
                    object = Ball::create(Vec2(i,j));
                    break;
                case tiledGid_oil:
                    object = Oil::create(Vec2(i, j));
                    break;
                case tiledGid_bomb:
                    object = Bomb::create(Vec2(i,j));
                    break;
                default:
                    object = Wall::create(Vec2(i,j));
                    break;
            }
            if(!object)
                continue;
            auto pos = objectLayer->convertToWorldSpace(objectLayer->getPositionAt(Vect(i, j)));
            object->setPosition(pos + ZEEK_TILED_OFFSET);
            if(objGid < tiledGid_wall)
                objectLayer->getTileAt(Vec2(i,j))->removeFromParentAndCleanup(true);
            pushGameObject(object);
            
            m_gameScene->addChild(object);
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
            obj->onDeath();
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

const Size& GameMgr::getMapSize()
{
    if(m_gameMap)
        return m_gameMap->getMapSize();
    else
        return Size::ZERO;
}
