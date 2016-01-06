//
//  GameMap.hpp
//  test01
//
//  Created by cyruslam on 16/12/15.
//
//

#ifndef GameMap_h
#define GameMap_h

//#include <stdio.h>
#include "cocos2d.h"

class GameMap : public cocos2d::Node
{
    /*
     plant for each size = 10 square
     type 0
     */
    
    enum BlockType {
        Non ,
        Wall ,
        Floor,
        Player,
        Enemry
    };
    
    cocos2d::Vec2 player_pos = cocos2d::Vec2::ZERO;
    
    const float edget = 100;
    cocos2d::Vec2 node_size = cocos2d::Vec2(edget, edget);
    cocos2d::Vector<cocos2d::Node*> plants;
    
    cocos2d::Sprite* CreateWall( std::string res_path , cocos2d::Vec2 pos , int categoryBit , int collisionBitmask , int contactTestBitmask);
    cocos2d::Sprite* CreateFloor( std::string res_path  , cocos2d::Vec2 pos);
    
    
    public :
    
    cocos2d::Vec2 GetPlayerPos();
    
    void BuildMap( std::string res_path_ground , cocos2d::Size n_size , int categoryBit , int collisionBitmask , int contactTestBitmask);

    
};


#endif /* GameMap_h */
