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
#include "GameMap.h"
#include "Charactor.h"

class InGameScene : public cocos2d::Layer
{
    cocos2d::Vector<cocos2d::Node*> bullets;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    //UI
    void init_UI();
    //map grend
    void init_map();
    
    // a selector callback
    void BackToMenuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGameScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    bool onContactBegan(cocos2d::PhysicsContact &contact);
};

//







#endif /* InGameScene_h */
