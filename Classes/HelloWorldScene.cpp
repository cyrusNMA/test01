#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    auto background_rect = DrawNode::create();
    background_rect->drawSolidRect(origin, visibleSize, Color4F(1, 0.5, 0, 1));
    background_rect->setPosition(Vec2::ZERO);
    this->addChild(background_rect);
    
    //add a start button
    auto startLableItem = MenuItemLabel::create(cocos2d::Label::createWithTTF("START", "fonts/Marker Felt.ttf", 25), CC_CALLBACK_1(HelloWorld::startGameCallBack, this));
    startLableItem->setPosition(Vec2(origin.x + visibleSize.width/2 ,
                                origin.y + visibleSize.height/2));
    
    auto lab_version = MenuItemLabel::create(cocos2d::Label::createWithTTF("Version : 0.1.5", "fonts/Marker Felt.ttf", 5));
    lab_version->setPosition(Vec2(origin.x + 10 ,origin.y + 10));
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "menu_normal.png",
                                           "menu_selected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width ,
                                origin.y + closeItem->getContentSize().height));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, startLableItem, lab_version, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->setName("menu");
    this->addChild(menu, 1);

    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);

    
    
    //player BGM
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/noname_01.mp3", true);
    

    //set the rolling background object
    {
        
        auto cnt_row = (int)(visibleSize.height / sp_egde_leng) + sp_spare_;
        auto cnt_collum = (int)(visibleSize.width / sp_egde_leng) + sp_spare_;
        
        for(int sp_idx = 0 ; sp_idx < cnt_row * cnt_collum ; sp_idx++){
            
            auto n_sp = Sprite::create("res/heart_64.png");
            n_sp->setPosition( Vec2(
                                    (int)(sp_idx % cnt_collum) * sp_egde_leng,
                                    (int)(sp_idx / cnt_collum) * sp_egde_leng ) );
            this->addChild(n_sp);
            bg_sp.push_back(n_sp);
        }
        
        this->schedule(schedule_selector(HelloWorld::RollingBackground));
        
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::startGameCallBack(Ref *pSender)
{
//    MessageBox("You pressed the start button. Windows Store Apps do not implement a close button.","Alert");

    auto loading_rect = DrawNode::create();
    loading_rect->drawSolidRect(origin, visibleSize, Color4F(0, 0, 0, 1));
    loading_rect->setPosition(Vec2::ZERO);
    loading_rect->setName("loading_splash");
    this->addChild(loading_rect);
    
    auto loading_text = Label::createWithTTF("Loading", "fonts/Marker Felt.ttf", 25);
    loading_text->setPosition(Vec2(visibleSize.width - loading_text->getContentSize().width - 10, 0 + loading_text->cocos2d::Node::getContentSize().height + 10));
    loading_text->setName("loading_text");
    this->addChild(loading_text);
    
    this->removeChildByName("menu");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    this->scheduleOnce(schedule_selector(HelloWorld::changeSceneCallBack), 3);
    
}

void HelloWorld::changeSceneCallBack(float dt)
{
    SceneManager::getInstance()->Goto(SceneManager::vailScene::InGame);
}

void HelloWorld::RollingBackground(float dt)
{
    auto cnt_row = (int)(visibleSize.height / sp_egde_leng) + sp_spare_;
    auto cnt_collum = (int)(visibleSize.width / sp_egde_leng) + sp_spare_;
    
    if( bg_sp.size() ){
        for(int sp_idx = 0 ; sp_idx < bg_sp.size() ; sp_idx++){
            auto cur_pos = bg_sp[sp_idx]->getPosition();
            
            cur_pos.x -= bg_sp_mvsp * dt;
            if( cur_pos.x + sp_egde_leng < 0 )
                cur_pos.x = (cnt_collum - 1) * sp_egde_leng ;
            
            cur_pos.y -= bg_sp_mvsp * dt;
            if( cur_pos.y + sp_egde_leng < 0 )
                cur_pos.y = (cnt_row - 1) * sp_egde_leng;
            
            bg_sp[sp_idx]->setPosition(cur_pos);
        }
    }
    
}


