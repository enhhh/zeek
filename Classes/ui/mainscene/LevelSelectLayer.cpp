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
    auto node = CSLoader::getInstance()->createNode("levelSelectLayer.csb");
    this->addChild(node);
       return true;
}