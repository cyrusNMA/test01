//
//  UT_Map.cpp
//  test01
//
//  Created by cyruslam on 3/1/16.
//
//

#include "UT_Map.h"

USING_NS_CC;

// Physics Category
enum class PhysicsCategory {
    None = 0,
    Player = 00000001, //1
    Monster = 00000010,    // 2
    Wall = 00000011, // 3
    Bullet = 00000100, //4
    All = PhysicsCategory::Monster | PhysicsCategory::Bullet | PhysicsCategory::Player / 3
};



Scene* UT_Map::createScene()
{
    // 'scene' is an autorelease object
    
//    auto scene = Scene::create();  // get normal scene
    auto scene = Scene::createWithPhysics(); //get Physics scene
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = UT_Map::create();
    
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool UT_Map::init(){
    
    if(!Layer::init()){
        return false;
    }
    
    //seeds the random number generator
    srand((unsigned int)time(nullptr));
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //create wall
    //If Full Paint FPS Droped to 12
    //
    test_map = new GameMap();
    test_map->BuildMap("res/map/block_01.jpg" , Size(18, 10), (int)PhysicsCategory::Wall, (int)PhysicsCategory::None, (int)PhysicsCategory::Player);
    this->addChild(test_map);

    log("GetPlayerPos() ? (%f, %f)",test_map->GetPlayerPos().x , test_map->GetPlayerPos().y);
    
    //create wall crasher
    if(true){
        body = cocos2d::DrawNode::create();
        body->drawSolidRect(Vec2(0,0), Vec2(10,25), Color4F(0.1, 0, 1, 1));
        body->setPosition(test_map->GetPlayerPos());
        test_map->addChild(body);
        body->setName("Player_body");
        body->setZOrder(1);
        
        auto body_phyBody = PhysicsBody::createBox(Size(body->getContentSize().width , body->getContentSize().height),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        body_phyBody->setDynamic(true);
        body_phyBody->setCategoryBitmask((int)PhysicsCategory::Player);
        body_phyBody->setCollisionBitmask((int)PhysicsCategory::None);
        body_phyBody->setContactTestBitmask((int)PhysicsCategory::Wall);
        body->setPhysicsBody(body_phyBody);
    }
    
    
    this->schedule(schedule_selector(UT_Map::Scheduler));
    
    
    //Set the Physics Collision notification
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(UT_Map::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}


    //***** ********* *****//
    //***** callbacks *****//
    //***** ********* *****//

void UT_Map::Scheduler(float dt){
    
//    log( "Scheduler() > Dealt Time ? %f" , dt);
    
//    if( !body )
        return;
    
    auto mov_sp = 100;
    
    auto n_pos = body->getPosition();
    
    if( body_move_r ){
        n_pos.x += mov_sp * dt;
//        if( n_pos.x > visibleSize.width )
//            n_pos.x = 0;
        
    }else{
        n_pos.x -= mov_sp * dt;
//        if( n_pos.x < 0 - body->getContentSize().width )
//            n_pos.x = visibleSize.width;
    }
    
    body->setPosition(n_pos);
    
}


bool UT_Map::onContactBegan(cocos2d::PhysicsContact &contact){
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
//    cocos2d::log( " nodeA name  %s" , nodeA->getName().c_str() );
//    cocos2d::log( " nodeB name  %s" , nodeB->getName().c_str() );
    
    if( nodeA == body || nodeB == body){
        body_move_r = !body_move_r;
    }else{
//        cocos2d::log( " can not match ");
    }
    
    return true;
}

///As Template methods

//callback
void UT_Map::Callback_(cocos2d::Ref* pSender){
    
}


bool UT_Map::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchBegan() called!" );
//    t_delta = cocos2d::Vec2(0,0);
//    t_start = sprit_touchball_state->getPosition();
//    player_atk = true;
    
    return true;
}

void UT_Map::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchMoved() called!" );
    auto t_cur = touch->getLocation();
//    t_delta = cocos2d::Vec2(  t_cur.x - t_start.x , t_cur.y - t_start.y );
//    sprit_touchball_move->setPosition( t_cur );
    
    //    return true;
}

void UT_Map::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchEnded() called!" );
//    t_delta = cocos2d::Vec2(0,0);
//    sprit_touchball_move->setPosition( sprit_touchball_state->getPosition());
//    
//    player_mv_R = player_mv_L = player_mv_U = player_mv_D = player_atk = false;
}