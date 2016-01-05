//
//  InGameScene.hpp
//  test01
//
//  Created by cyruslam on 14/12/15.
//
//

#ifndef InGameScene_h
#define InGameScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameMap.h"
#include "Charactor.h"

class InGameScene : public cocos2d::Layer
{
    // Physics Category
    enum class PhysicsCategory {
        None = 0,
        Player = 00000001, //1
        Monster = 00000010,    // 2
        Wall = 00000011, // 3
        Bullet = 00000100, //4
        All = PhysicsCategory::Monster | PhysicsCategory::Bullet | PhysicsCategory::Player / 3
    };
    
    //Player
    Player* test_player;
    cocos2d::Vector<cocos2d::Node*> bullets;
    
    //Map
    GameMap * test_map;
    
    //instance of Touch control
    int t_marge = 10;
    bool player_atk = false;
    bool player_mv_L = false;
    bool player_mv_R = false;
    bool player_mv_U = false;
    bool player_mv_D = false;
        //calcu
    cocos2d::Vec2 t_start = cocos2d::Vec2(0,0);
    cocos2d::Vec2 t_delta = cocos2d::Vec2(0,0);
        //Image
    cocos2d::Sprite* sprit_touchball_state = nullptr;
    cocos2d::Sprite* sprit_touchball_move = nullptr;
    
    
    
public:

    //Super Classes
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //UI
    void init_UI();
    //map grend
    void init_map();
    
    //***** Player cases *****//
    void _schedule(float dt);
//    void _move(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void _attack_near();
    void _attack_far();

    //***** callbacks *****//
    void BackToMenuCallback(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    bool onContactBegan(cocos2d::PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGameScene);
};

//







#endif /* InGameScene_h */
