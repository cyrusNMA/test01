//
//  SceneManager.cpp
//  test01
//
//  Created by cyruslam on 16/12/15.
//
//

#include "SceneManager.h"


static SceneManager* s_pSharedSceneManager = nullptr;
int cur_count;
SceneManager::vailScene cur_enum_idx;


SceneManager::SceneManager(){
    cur_count = 0;
    cur_enum_idx = vailScene::Menu;
}

SceneManager::~SceneManager(){
    
}

SceneManager* SceneManager::getInstance(){
    
    if( !s_pSharedSceneManager ){
        s_pSharedSceneManager = new SceneManager();
    }
    return s_pSharedSceneManager;
    
}

cocos2d::Scene* SceneManager::getScene(){
    switch( cur_enum_idx ){
        case vailScene::Menu :
            return HelloWorld::createScene();
            break;
        case vailScene::InGame :
            return InGameScene::createScene();
            break;
        case vailScene::UT_player :
            return UT_Player::createScene();
            break;
        case vailScene::UT_map :
            return UT_Map::createScene();
            break;
            
    }
    
    return nullptr;
}

void SceneManager::Goto( SceneManager::vailScene enum_idx ){
    // initialize director
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = cocos2d::GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    // create a scene. it's an autorelease object
    cur_enum_idx = enum_idx;
    auto scene = getScene();
    
    // run
    if( cur_count == 0 ){
        director->runWithScene(scene);
    }else if( cur_count > 0 ){
        director->pushScene(scene);
    }
    
    cur_count++;
}

void SceneManager::Pop(){
    auto director = cocos2d::Director::getInstance();
    director->popScene();
    cur_count--;
}