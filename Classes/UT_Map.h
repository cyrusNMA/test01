//
//  UT_Map.hpp
//  test01
//
//  Created by cyruslam on 3/1/16.
//
//

#ifndef UT_Map_h
#define UT_Map_h

//#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameMap.h"


class UT_Map : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::DrawNode * body = nullptr;
    bool body_move_r = true;
    
    GameMap * test_map;
    
    public :
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //***** Test case *****//
    cocos2d::Sprite* CreateWall( std::string res_path , cocos2d::Vec2 pos);
    cocos2d::Sprite* CreateFloor( std::string res_path  , cocos2d::Vec2 pos);
    void BuildMap( std::string res_path_ground , cocos2d::Size n_size);
    
    //***** callbacks *****//
    void Scheduler(float dt);
    
    //Physics Callbacl of object collisioned
    bool onContactBegan(cocos2d::PhysicsContact &contact);
    
    void Callback_(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //Implement the "static create()" method manually
    CREATE_FUNC(UT_Map);
};

#endif /* UT_Map_h */
