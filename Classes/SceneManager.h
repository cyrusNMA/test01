//
//  SceneManager.hpp
// used to handle all scene
//  test01
//
//  Created by cyruslam on 15/12/15.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "base/uthash.h"

//**** Scene
#include "HelloWorldScene.h"
#include "InGameScene.h"

//**** Unit Test
#include "UT_Player.h"

class SceneManager
{
    
    
    private :
    
        cocos2d::Scene* getScene();
    
    public :
    
        enum class vailScene {
            Menu
            , InGame
            , UT_player
        };
    
        SceneManager();
        virtual ~SceneManager();
    
        static SceneManager* getInstance();

        void Add( cocos2d::Scene n_scene , char scenes);
        void Goto( SceneManager::vailScene enum_idx );
        void Pop();
};

#endif /* SceneManager_hpp */
