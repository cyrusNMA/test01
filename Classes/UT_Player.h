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
#include "Charactor.h"



class UT_Player : public cocos2d::Layer
{
    cocos2d::Vector<cocos2d::Node*> bullets;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    //***** test cases *****//
    void _move();
    void _attack_near();
    void _attack_far();
    
    //***** callbacks *****//
    void Callback_(cocos2d::Ref* pSender);
    
//    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
//    bool onContactBegan(cocos2d::PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(UT_Player);
};

#endif /* ut_Player_h */
