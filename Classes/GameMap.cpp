//
//  GameMap.cpp
//  test01
//
//  Created by cyruslam on 16/12/15.
//
//

#include "GameMap.h"

USING_NS_CC;

cocos2d::Sprite* GameMap::CreateWall( std::string res_path , cocos2d::Vec2 pos , int categoryBit , int collisionBitmask , int contactTestBitmask){
    
    auto n_wall_ = Sprite::create(res_path);
    n_wall_->setName("Wall");
    n_wall_->setPosition(Vec2(n_wall_->getContentSize().width * pos.x, n_wall_->getContentSize().height * pos.y));
    
    this->addChild(n_wall_);
    
    if(true){
        auto wall_Size = n_wall_->getContentSize();
        auto n_physicsBody = PhysicsBody::createBox(Size(wall_Size.width , wall_Size.height),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        
        
        n_physicsBody->setDynamic(true);
        n_physicsBody->setCategoryBitmask( categoryBit );
        n_physicsBody->setCollisionBitmask( collisionBitmask );
        n_physicsBody->setContactTestBitmask( contactTestBitmask );
        
        //Set Physics body to the object wall
        n_wall_->setPhysicsBody(n_physicsBody);
    }
    
    return n_wall_;
}

cocos2d::Sprite* GameMap::CreateFloor( std::string res_path , cocos2d::Vec2 pos ){
    
    auto n_wall_ = Sprite::create(res_path);
    n_wall_->setName("Floor");
    n_wall_->setPosition(Vec2(n_wall_->getContentSize().width * pos.x, n_wall_->getContentSize().height * pos.y));
    this->addChild(n_wall_);
    
    auto wall_Size = n_wall_->getContentSize();
    
    return n_wall_;
}

void GameMap::BuildMap( std::string res_path_ground , cocos2d::Size n_size , int categoryBit , int collisionBitmask , int contactTestBitmask){
    
    int h_cnt = n_size.width;
    int v_cnt = n_size.height;
    for(int w_idx = 0 ; w_idx < h_cnt * v_cnt ; w_idx ++ )
    {
        //calcu a new pos for each block
        auto n_pos = Vec2( (w_idx % h_cnt), (int)(w_idx / h_cnt));
        
        //Case where do plast the wall
        if( (w_idx % h_cnt == 0 || w_idx % h_cnt == h_cnt-1) ||
           ((int)(w_idx / h_cnt) == 0 || (int)(w_idx / h_cnt) == v_cnt-1)){
            CreateWall(res_path_ground , n_pos , categoryBit , collisionBitmask , contactTestBitmask);
        }else{
            CreateFloor(res_path_ground , n_pos);
            
            //TODO :: User Start Position
            
            //TODO :: Monster Position
            
            //TODO :: Block Position
            
            //TODO :: Item Position
        }
        
    }
    
    
}


