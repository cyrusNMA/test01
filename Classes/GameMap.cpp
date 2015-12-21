//
//  GameMap.cpp
//  test01
//
//  Created by cyruslam on 16/12/15.
//
//

#include "GameMap.h"



void GameMap::Grend( cocos2d::Size screem_size )
{
    //create a node with size
    
    //clean the list once
    plants.empty();
    
    int cell_lenght = 3;
    for(int cell_i = 0 ; cell_i < cell_lenght * cell_lenght ; cell_i++){
        auto n_plast_ = cocos2d::DrawNode::create();
        n_plast_->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(10, 10), cocos2d::Color4F(1,1,1,1));
        n_plast_->setPosition( (cell_i % cell_lenght) * node_size.x , (int)(cell_i / cell_lenght) * node_size.y);
        
        auto plants_outline = cocos2d::DrawNode::create();
        plants_outline->drawRect(cocos2d::Vec2::ZERO, node_size, cocos2d::Color4F::GREEN);
        n_plast_->addChild(plants_outline);
        
        //add to list
        plants.pushBack(n_plast_);
        this->addChild(plants.at(cell_i));
    }
    
    //added to child
    
}

bool GameMap::IsInsideTheMap( cocos2d::Vec2 n_pos )
{
    
    
    
    return false;
}
