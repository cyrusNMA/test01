#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"  

class HelloWorld : public cocos2d::Layer
{
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    int sp_egde_leng = 64;
    int bg_sp_mvsp = 50;                    //move speed
    int sp_spare_ = 3;
    std::vector<cocos2d::Sprite*> bg_sp;    //rolling background sprite list
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void startGameCallBack(cocos2d::Ref* pSender);
    void changeSceneCallBack(float dt);
    
    //Background Roller
    void RollingBackground(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
