//
//  GameScene.cpp
//  zeek
//
//  Created by enh on 15/3/29.
//
//

#include "GameScene.h"

#define ZEEK_GID 2

GameScene::GameScene()
: m_gameMap(nullptr)
, m_zeek(nullptr)
, m_objectLayer(nullptr)
{
    
}

GameScene::~GameScene()
{
    
}

GameScene*GameScene::create()
{
    auto ptr = new GameScene();
    if(ptr && ptr->init())
    {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
        ptr->initAnimation();
        ptr->autorelease();
        //test
        ptr->loadGameMap("test.tmx");
        //endTests
        return ptr;
        
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}


void GameScene::initAnimation()
{
    Vector<SpriteFrame*> animations;
    char str[100]={0};
    Animation* animation = nullptr;
    
#define LOAD_ANIMAION(name,frameSize) \
    for(int i = 1; i<= frameSize; i++) \
    {                                   \
        sprintf(str,"%s%d.png",#name,i); \
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str); \
        animations.pushBack(frame);\
    }\
    animation = Animation::createWithSpriteFrames(animations,0.5f);\
    AnimationCache::getInstance()->addAnimation(animation,#name); \
    animations.clear();
    
    
    LOAD_ANIMAION(zeek_rest, 4)
    LOAD_ANIMAION(zeed_walk_east, 4)
    LOAD_ANIMAION(zeed_walk_north, 4)
    LOAD_ANIMAION(zeed_walk_south, 4)
    LOAD_ANIMAION(dinosaur_east, 4)
    LOAD_ANIMAION(dinosaur_north, 4)
    LOAD_ANIMAION(dinosaur_south, 4)
    
}

bool GameScene::loadGameMap(const std::string &fileName)
{
    if(m_gameMap)
        m_gameMap->removeFromParentAndCleanup(true);
    m_gameMap = TMXTiledMap::create(fileName);
    if(!m_gameMap)
        return false;
    this->addChild(m_gameMap);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onMapTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onMapTouchMove,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onMapTouchEnd, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_gameMap);
    
    parseGameMap(m_gameMap->getLayer("hazard"));
    return true;
}

bool GameScene::parseGameMap(cocos2d::TMXLayer *objectLayer)
{
    if(!m_gameMap || !objectLayer)
        return false;
    auto size = objectLayer->getLayerSize();
    for(int i = 0; i < size.width; i++)
    {
        for(int j = 0 ; j < size.height;j++)
        {
            if(objectLayer->getTileGIDAt(Vec2(i,j)) == ZEEK_GID)
            {
                objectLayer->getTileAt(Vec2(i,j))->removeFromParentAndCleanup(true);
                if(!m_zeek)
                {
                    m_zeek = Zeek::create(Vec2(i,j));
                    this->addChild(m_zeek);
                }
                auto pos = objectLayer->convertToWorldSpace(objectLayer->getPositionAt(Vect(i,j)));
                m_zeek->setPosition(pos);
            }
            
        }
    }
    return true;
}

bool GameScene::onMapTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 locationInNode = m_gameMap->convertToNodeSpace(touch->getLocation());
    Size s = m_gameMap->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    
    if (rect.containsPoint(locationInNode))
    {
        this->setColor(Color3B::RED);
        return true;
    }
    return false;
}

void GameScene::onMapTouchMove(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void GameScene::onMapTouchEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 locationInNode = m_gameMap->convertToNodeSpace(touch->getLocation());
    int x = locationInNode.x / m_gameMap->getTileSize().width;
    int y = locationInNode.y / m_gameMap->getTileSize().height;
    m_zeek->walkToPosition(Vect(x,y));
}



