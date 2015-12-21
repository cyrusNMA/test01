//
//  ut_Player.cpp
//  test01
//
//  Created by cyruslam on 20/12/15.
//
//

#include "UT_Player.h"


USING_NS_CC;

//Size visibleSize;
//Vec2 origin;

Player* test_player;
Enemy* test_enemy;

Scene* UT_Player::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = UT_Player::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool UT_Player::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    test_player = new Player();
    this->addChild(test_player);
    log( "UT_Player::init() test_player set done" );
//
    test_enemy = new Enemy();
    this->addChild(test_enemy);
    log( "UT_Player::init() test_enemy set done" );
    
    //Menu - test list

    
    auto btn_move = MenuItemImage::create("res/button-blue.png", "res/button-purple.png", CC_CALLBACK_0(UT_Player::_move, this));
    btn_move->setPosition( 0 , visibleSize.height );
    
    auto menu = Menu::create(btn_move , NULL);
    menu->setPosition(origin.x + visibleSize.width/2 , origin.y);
    this->addChild(menu);
    log( "UT_Player::init() menu set done" );
    
    //set rand
    srand((unsigned int)time(nullptr));
    
    //
//    this->schedule(schedule_selector(HelloWorld::addMonster), 1.5);
    
    return true;
}

void UT_Player::_move()
{
    log( "UT_Player::_move() called !" );
    
    //stop all actions
    test_player->stopAllActions();
    
    //reset pos
    test_player->setPosition(Vec2(500, 500));
    
    //run action
    auto act_move = MoveTo::create(10, Vec2(1000, 1000));
    test_player->runAction(act_move);
}

void UT_Player::_attack_near()
{
    log( "UT_Player::_attack_near() called !" );
}

void UT_Player::_attack_far()
{
    log( "UT_Player::_attack_far() called !" );
}

//callback
void UT_Player::Callback_(cocos2d::Ref* pSender){
    
}