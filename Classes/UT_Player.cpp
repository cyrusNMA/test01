//
//  ut_Player.cpp
//  test01
//
//  Created by cyruslam on 20/12/15.
//
//

#include "UT_Player.h"

USING_NS_CC;


bool player_atk = false;
bool player_mv_L = false;
bool player_mv_R = false;
bool player_mv_U = false;
bool player_mv_D = false;

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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    test_player = new Player();
    test_player->hp = 10;
    test_player->speed = 10;
    test_player->attack = 1;
    test_player->SetAttackFeq(0.1);
    auto body = cocos2d::DrawNode::create();
    body->drawSolidRect(Vec2(0,0), Vec2(10,25), Color4F(0.1, 0, 1, 1));
    test_player->addChild(body);
    test_player->setPosition(Vec2(visibleSize.width/4, visibleSize.height/2));
    this->addChild(test_player);
    log( "UT_Player::init() test_player set done" );
//
    test_enemy = new Enemy();
    this->addChild(test_enemy);
    log( "UT_Player::init() test_enemy set done" );
    
    //Touch
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(UT_Player::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(UT_Player::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(UT_Player::onTouchEnded, this);
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
 
    log( "UT_Player::init() menu set done" );
    
    //set rand
    srand((unsigned int)time(nullptr));
    
    //
    this->schedule(schedule_selector(UT_Player::_schedule));
    
    return true;
}

void UT_Player::_schedule(float dt)
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
    if(player_mv_R){
        Vec2 pos_1 = test_player->getPosition();
        pos_1.x += test_player->speed;
        if( pos_1.x > visibleSize.width )
            pos_1.x = 0;
        test_player->setPosition(pos_1);
    }else if(player_mv_L){
        Vec2 pos_1 = test_player->getPosition();
        pos_1.x -= test_player->speed;
        if( pos_1.x < 0 )
            pos_1.x = visibleSize.width;
        test_player->setPosition(pos_1);
    }
    
    if(player_mv_U){
        Vec2 pos_1 = test_player->getPosition();
        pos_1.y += test_player->speed;
        if( pos_1.y > visibleSize.height )
            pos_1.y = 0;
        test_player->setPosition(pos_1);
    }else if(player_mv_D){
        Vec2 pos_1 = test_player->getPosition();
        pos_1.y -= test_player->speed;
        if( pos_1.y < 0 )
            pos_1.y = visibleSize.height;
        test_player->setPosition(pos_1);
    }
}

void UT_Player::_move(Ref* sender, ui::Widget::TouchEventType type)
{
    log( "UT_Player::_move() called !" );
    
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            log( "UT_Player::_move() called  >> TouchEventType::BEGAN" );
            break;
        case ui::Widget::TouchEventType::ENDED:
            log( "UT_Player::_move() called  >> TouchEventType::ENDED" );
            break;
        case ui::Widget::TouchEventType::MOVED:
            log( "UT_Player::_move() called  >> TouchEventType::MOVED" );
            break;
        case ui::Widget::TouchEventType::CANCELED:
            log( "UT_Player::_move() called  >> TouchEventType::CANCELED" );
            break;
        default:
            log( "UT_Player::_move() called  >> default" );
            break;
    }
}


void UT_Player::_attack_near()
{
    log( "UT_Player::_attack_near() called !" );
}

void UT_Player::_attack_far()
{
    
    auto n_pos = test_player->getPosition();
    n_pos.x += 200;
    auto bullet = test_player->EmitOneBullet(n_pos);
    if( bullet != nullptr ){
        this->addChild(bullet);
        log( "UT_Player::_attack_far() >> add bullet !" );
    }else{
        log( "UT_Player::_attack_far() >> bullet is null !" );
    }
}

//callback
void UT_Player::Callback_(cocos2d::Ref* pSender){
    
}


bool UT_Player::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchBegan() called!" );
    t_delta = cocos2d::Vec2(0,0);
    t_start = sprit_touchball_state->getPosition();
    player_atk = true;
    
    return true;
}

void UT_Player::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchMoved() called!" );
    auto t_cur = touch->getLocation();
    t_delta = cocos2d::Vec2(  t_cur.x - t_start.x , t_cur.y - t_start.y );
    sprit_touchball_move->setPosition( t_cur );
    
//    return true;
}

void UT_Player::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    log( "UT_Player::onTouchEnded() called!" );
    t_delta = cocos2d::Vec2(0,0);
    sprit_touchball_move->setPosition( sprit_touchball_state->getPosition());
    
    player_mv_R = player_mv_L = player_mv_U = player_mv_D = player_atk = false;
}