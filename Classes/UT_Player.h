//
//  ut_Player.hpp
//  test01
//
//  Created by cyruslam on 20/12/15.
//
//

#ifndef ut_Player_h
#define ut_Player_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Charactor.h"



class UT_Player : public cocos2d::Layer
{
    cocos2d::Vector<cocos2d::Node*> bullets;
    Player* test_player;
    Enemy* test_enemy;
    
    int t_marge = 10;
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    //instance of Touch control
    cocos2d::Vec2 t_start = cocos2d::Vec2(0,0);
    cocos2d::Vec2 t_delta = cocos2d::Vec2(0,0);
    
    cocos2d::Sprite* sprit_touchball_state = nullptr;
    cocos2d::Sprite* sprit_touchball_move = nullptr;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    //***** test cases *****//
    void _schedule(float dt);
    void _move(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void _attack_near();
    void _attack_far();
    
    //***** callbacks *****//
    void Callback_(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
//    bool onContactBegan(cocos2d::PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(UT_Player);
};

#endif /* ut_Player_h */
