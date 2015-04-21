//
//  LevelSelectLayer.cpp
//  zeek
//
//  Created by enh on 15/4/21.
//
//

#include "LevelSelectLayer.h"

LevelSelectLayer * LevelSelectLayer::create()
{
    auto ptr = new LevelSelectLayer();
    if(ptr && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return nullptr;
}

bool LevelSelectLayer::init()
{
    if(!Layer::init())
        return false;
    
    //load resource
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/levelSelect/AE_HaiO.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui/levelSelect/AE_JinYu.ExportJson");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/levelSelect/LevelSImage.plist");
    
    auto ScreenSize = Director::getInstance()->getVisibleSize();
    auto ScreenCenter = Vec2(ScreenSize.width/2,ScreenSize.height/2);
    auto WinSize = Director::getInstance()->getWinSize();
    //背景
    Scale9Sprite *ml_bg = Scale9Sprite::createWithSpriteFrameName("Level_BG.png");
    ml_bg->setContentSize(ScreenSize);
    ml_bg->setPosition(ScreenCenter);
    this->addChild(ml_bg);
    //背景天上的白条
    auto ml_bgBai = Sprite::createWithSpriteFrameName("Level_BG_BaiTiao.png");
    ml_bgBai->setAnchorPoint(Vec2(0.5, 1.0));
    ml_bgBai->setPosition(Vec2(ScreenCenter.x, WinSize.height));
    this->addChild(ml_bgBai);
    
    //背景蓝色的水
    auto ml_bgWater = Sprite::createWithSpriteFrameName("Level_BG_Water.png");
    ml_bgWater->setAnchorPoint(Vec2(0.5, 0.0));
    ml_bgWater->setPosition(Vec2(ScreenCenter.x, 0));
    this->addChild(ml_bgWater);
    
    //云朵
    auto pCloud1 = Sprite::createWithSpriteFrameName("Level_Cloud1.png");
    pCloud1->setPosition(Vec2(WinSize.width * 0.1, WinSize.height * 0.75));
    this->addChild(pCloud1);
    
    auto pCloud2 = Sprite::createWithSpriteFrameName("Level_Cloud2.png");
    pCloud2->setPosition(Vec2(WinSize.width * 0.35, WinSize.height * 0.77));
    this->addChild(pCloud2);
    
    auto pCloud3 = Sprite::createWithSpriteFrameName("Level_Cloud3.png");
    pCloud3->setPosition(Vec2(WinSize.width * 0.75, WinSize.height * 0.8));
    this->addChild(pCloud3);
    
    auto pCloud4 = Sprite::createWithSpriteFrameName("Level_Cloud4.png");
    pCloud4->setPosition(Vec2(WinSize.width * 0.95, WinSize.height * 0.78));
    this->addChild(pCloud4);
    
    auto pos1 = pCloud1->getPosition() + Vec2(200 , 0);
    auto pos2 = pCloud2->getPosition() + Vec2(300 , 0);
    auto pos3 = pCloud3->getPosition() + Vec2(200 , 0);
    auto pos4 = pCloud4->getPosition() + Vec2(200 , 0);
    
    pCloud1->runAction(RepeatForever::create(Sequence::create(MoveTo::create(50, pos1), \
                                                              MoveTo::create(50, pCloud1->getPosition()), nullptr)));
    pCloud2->runAction(RepeatForever::create(Sequence::create(MoveTo::create(50, pos2), \
                                                              MoveTo::create(50, pCloud2->getPosition()), nullptr)));
    pCloud3->runAction(RepeatForever::create(Sequence::create(MoveTo::create(50, pos3), \
                                                              MoveTo::create(50, pCloud3->getPosition()), nullptr)));
    pCloud4->runAction(RepeatForever::create(Sequence::create(MoveTo::create(50, pos4), \
                                                              MoveTo::create(50, pCloud4->getPosition()), nullptr)));
    
    
    //海鸥
    Vec2 haioPos[3] = {Vec2(224, 372),Vec2(580, 478),Vec2(844, 348)};
    for (int i = 0; i<3; i++) {
        auto haiou = cocostudio::Armature::create("AE_HaiO");
        haiou->setPosition(Vec2(haioPos[i].x,haioPos[i].y));
        this->addChild(haiou);
        haiou->getAnimation()->playWithIndex(i);
        //调试
        //_Global.addEditNode(haiou);
    }
    return true;
}