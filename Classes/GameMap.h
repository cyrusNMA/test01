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
    const float edget = 100;
    cocos2d::Vec2 node_size = cocos2d::Vec2(edget, edget);
    cocos2d::Vector<cocos2d::Node*> plants;
    
    public :
    
    void Grend( cocos2d::Size screem_size );
    
    
    bool IsInsideTheMap( cocos2d::Vec2 n_pos );
};

class GmaeMapPlant : public cocos2d::Node
{
};

#endif /* GameMap_h */
