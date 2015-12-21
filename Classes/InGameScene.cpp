//
//  InGameScene.cpp
//  test01
//
//  Created by cyruslam on 14/12/15.
//
//

#include "InGameScene.h"

USING_NS_CC;


Size visibleSize;
Vec2 origin;

const std::string Name_player = "player";

Scene* InGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = InGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //set-up touch
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
    
    //set up ui
    init_UI();
    
    //set up ingame object
    init_map();
    
    //set the touch event listener
    auto player_0 = this->getChildByName(Name_player);
    if( player_0 != nullptr ){
            this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, player_0);
    }
    
    return true;
}

void InGameScene::init_UI()
{
    auto backBtn = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(InGameScene::BackToMenuCallback, this));
    
    backBtn->setPosition(Vec2(origin.x + visibleSize.width - backBtn->getContentSize().width/2 ,origin.y + backBtn->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("This is InGame Scene", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
}
void InGameScene::init_map()
{
    //new map layer
    auto map_0 = new GameMap();
    map_0->Grend( visibleSize );
    map_0->setPosition(origin.x, origin.y);
    
    auto player_0 = new Player();
    player_0->setName(Name_player);
    player_0->setPosition(0 , 0);
    {
        //set the skin for the player
        auto skin = cocos2d::DrawNode::create();
        skin->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(10, 10), cocos2d::Color4F(1,0,0,1));
        //make node centered with x
        skin->setPosition( skin->getContentSize().width/2 , 0);
        player_0->addChild( skin );
    }
    
    //init bullets
    for(int i = 0 ; i < 1 ; i++){
        auto n_bullet = cocos2d::DrawNode::create();
        n_bullet->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(10, 10), cocos2d::Color4F(1,0.5,0,1));
        bullets.pushBack(n_bullet);
    }

    this->addChild(map_0 , 2);
    this->addChild(player_0 , 2);
}

void InGameScene::BackToMenuCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        MessageBox("You pressed the close button. CC_TARGET_PLATFORM == IOS","Alert");
    exit(0);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            MessageBox("You pressed the close button. CC_TARGET_PLATFORM == ANDROID","Alert");
    exit(0);
#endif
}

/***** on touch *****/
bool InGameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Vec2 touchLocation = touch->getLocation();
//    Vec2 offset = touchLocation - _player->getPosition();
  
    auto player_0 = this->getChildByName(Name_player);
    if( player_0 != nullptr ){
        
        float eachMoveDuration_long = 100;
        
        auto dest = std::sqrt(std::pow(player_0->getPositionX() - touchLocation.x, 2) + std::pow(player_0->getPositionY() - touchLocation.y, 2));
        
        auto actionMove = MoveTo::create(dest/eachMoveDuration_long, touchLocation);
        player_0->stopAllActions();
        player_0->runAction(Sequence::create(actionMove, nullptr));
    }else{
        MessageBox("player not exist","Alert");
    }
    
    return true;
}

bool InGameScene::onContactBegan(PhysicsContact &contact)
{
//    auto nodeA = contact.getShapeA()->getBody()->getNode();
//    auto nodeB = contact.getShapeB()->getBody()->getNode();
//    
//    nodeA->removeFromParent();
//    nodeB->removeFromParent();
    return true;
}

