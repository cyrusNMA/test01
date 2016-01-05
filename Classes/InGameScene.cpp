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
    
    
    //set up ingame object
    init_map();
    
    //set up ui
    init_UI();
    
    this->schedule(schedule_selector(InGameScene::_schedule));
    
    
    //Set the Physics Collision notification
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(InGameScene::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void InGameScene::init_UI()
{
    // 1 ----- Exit Button
    auto backBtn = MenuItemImage::create("menu_normal.png","menu_selected.png",CC_CALLBACK_1(InGameScene::BackToMenuCallback, this));
    backBtn->setPosition(Vec2(origin.x + visibleSize.width - backBtn->getContentSize().width ,origin.y + visibleSize.height - backBtn->getContentSize().height));
    auto menu = Menu::create(backBtn, NULL);   // create menu, it's an autorelease object
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    // 2 ------ BackGround
    
    
    // 3 ------ set-up Touch
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, test_player);
    
    //Set a touch ball for viual
    sprit_touchball_state = cocos2d::Sprite::create("res/button-blue.png");
    sprit_touchball_state->setPosition(cocos2d::Vec2(visibleSize.width - 80 ,visibleSize.height/2 ));
    sprit_touchball_state->setScale(30 / sprit_touchball_state->getContentSize().width);
    this->addChild(sprit_touchball_state);
    
    //Make a moveable touchball
    sprit_touchball_move = cocos2d::Sprite::create("res/button-purple.png");
    sprit_touchball_move->setPosition(cocos2d::Vec2(visibleSize.width - 80 ,visibleSize.height/2 ));
    sprit_touchball_move->setScale(30 / sprit_touchball_state->getContentSize().width);
    this->addChild(sprit_touchball_move);
    
}
void InGameScene::init_map()
{
    //new map layer
//    auto map_0 = new GameMap();
    //If Full Paint FPS Droped to 12 in similter
    test_map = new GameMap();
    test_map->BuildMap("res/map/block_01.jpg" , Size(30, 25), (int)PhysicsCategory::Wall, (int)PhysicsCategory::None, (int)PhysicsCategory::Player);
    this->addChild(test_map);
    
    test_player = new Player();
    test_player->hp = 10;
    test_player->speed = 100;
    test_player->attack = 1;
    test_player->setName("Player");
    test_player->SetAttackFeq(0.1);
    test_player->SetBody("");
    test_player->setPosition(Vec2(visibleSize.width/4, visibleSize.height/2));
    test_player->setZOrder(1);
    test_map->addChild(test_player); //*****
    //create wall crasher
    if(true){
        
        auto play_size = test_player->getChildByName("body")->getContentSize();
        auto body_phyBody = PhysicsBody::createBox(Size(play_size.width , play_size.height),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body_phyBody->setDynamic(true);
        body_phyBody->setCategoryBitmask((int)PhysicsCategory::Player);
        body_phyBody->setCollisionBitmask((int)PhysicsCategory::None);
        body_phyBody->setContactTestBitmask((int)PhysicsCategory::Wall);
        test_player->setPhysicsBody(body_phyBody);
    }


}

void InGameScene::_schedule(float dt)
{
    //    log( "UT_Player::_schedule() called !" );
    
    //Touch ball calculate
    {
        // move X
        if( t_delta.x > t_marge ){
            player_mv_R = true;
            player_mv_L = false;
        }else if(t_delta.x < -t_marge){
            player_mv_R = false;
            player_mv_L = true;
        }else{
            player_mv_R = player_mv_L = false;
        }
        
        //Move Y
        if( t_delta.y > t_marge ){
            player_mv_U = true;
            player_mv_D = false;
        }else if(t_delta.y < -t_marge){
            player_mv_U = false;
            player_mv_D = true;
        }else{
            player_mv_U = player_mv_D = false;
        }
    }
    
    //Player Fire
    if(player_atk){
        _attack_far();
    }
    
    //Player move
    auto pl_sp = test_player->speed * dt;
    auto map_sp = test_player->speed * dt;
    auto pos_ = test_player->getPosition();
    auto pos_map = test_map->getPosition();
    if(player_mv_R){  // Move Horistal
        pos_.x += pl_sp;
        pos_map.x -= map_sp;
//        if( pos_1.x > visibleSize.width ) pos_1.x = 0;
    }else if(player_mv_L){
        pos_.x -= pl_sp;
        pos_map.x += map_sp;
//        if( pos_1.x < 0 ) pos_1.x = visibleSize.width;
    }
    
    if(player_mv_U){   // Move Vertical
        pos_.y += pl_sp;
        pos_map.y -= map_sp;
//        if( pos_1.y > visibleSize.height ) pos_1.y = 0;
    }else if(player_mv_D){
        pos_.y -= pl_sp;
        pos_map.y += map_sp;
//        if( pos_1.y < 0 ) pos_1.y = visibleSize.height;
    }
    test_player->setPosition(pos_);
    test_map->setPosition(pos_map);
}



void InGameScene::_attack_near()
{
    log( "UT_Player::_attack_near() called !" );
}

void InGameScene::_attack_far()
{
    
    auto n_pos = test_player->getPosition();
    n_pos.x += 200;
    auto bullet = test_player->EmitOneBullet(n_pos);
    if( bullet != nullptr ){
        test_map->addChild(bullet); ////*****
//        log( "UT_Player::_attack_far() >> add bullet !" );
    }else{
        log( "UT_Player::_attack_far() >> bullet is null !" );
    }
}



    //***** ********* *****//
    //***** callbacks *****//
    //***** ********* *****//

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
//    log( "UT_Player::onTouchBegan() called!" );
    t_delta = cocos2d::Vec2(0,0);
    t_start = sprit_touchball_state->getPosition();
    player_atk = true;
    
    return true;
}

void InGameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
//    log( "UT_Player::onTouchMoved() called!" );
    auto t_cur = touch->getLocation();
    t_delta = cocos2d::Vec2(  t_cur.x - t_start.x , t_cur.y - t_start.y );
    sprit_touchball_move->setPosition( t_cur );
    
    //    return true;
}

void InGameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
//    log( "UT_Player::onTouchEnded() called!" );
    t_delta = cocos2d::Vec2(0,0);
    sprit_touchball_move->setPosition( sprit_touchball_state->getPosition());
    
    player_mv_R = player_mv_L = player_mv_U = player_mv_D = player_atk = false;
}

bool InGameScene::onContactBegan(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    
    
    //cases
    if( nodeA == test_player || nodeB == test_player ){
        
        //case what is object
        cocos2d::log( " nodeA name  %s" , nodeA->getName().c_str() );
        cocos2d::log( " nodeB name  %s" , nodeB->getName().c_str() );
        
    }else if( false ){
        //case bullet
        
        //if Player
        
        //if Enermy
        
        //if Wall
    }else if( false ){
    
    }
    
//    nodeA->removeFromParent();
//    nodeB->removeFromParent();
    return true;
}

