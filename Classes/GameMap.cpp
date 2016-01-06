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

//********                   ********//
//********  Public Function  ********//
//********                   ********//

cocos2d::Vec2 GameMap::GetPlayerPos()
{
    return player_pos;
}

void GameMap::BuildMap( std::string res_path_ground , cocos2d::Size n_size , int categoryBit , int collisionBitmask , int contactTestBitmask){
    
    int h_cnt = n_size.width;
    int v_cnt = n_size.height;
    int total_cnt = h_cnt * v_cnt;
    
    int floor_plan[total_cnt];  //create
    
    //grenenrate a map layout within the size
    /*
     e.g::
     nnnWWWWWWWWnnnnnn
     nnWffffffffWnnnnn
     nnnWffffffffWnnnn
     nnnnnnWffffffWnnn
     nnnnnWffffffWnnnn
     nnnnnnWWWWWWnnnnn <-- initial
    */
    //Ver 2
    {
        int max_non = (int)(h_cnt/3);
        int l_cnt = 1 + rand() % (int)( h_cnt / 3); //for initial
        int r_cnt = 1 + rand() % (int)( h_cnt / 3); //for initial
        int player_pos_y = 1 + rand() % (v_cnt - 1); // rand the player pos Y
        int player_pos_x = -1;
        log( "init >> l_cnt ? %i , r_cnt ? %i " , l_cnt , r_cnt);
        
        //Fill non Type first
        // Fill on the Left and Right First
        for(int v_idx = 0 ; v_idx < v_cnt ; v_idx ++ ) //per roll
        {
            
            //Do follow the initial pos to have change
            if( v_idx > 0 ){
                l_cnt += (  rand() % 3 - 1 );
                if( l_cnt < 1 )
                    l_cnt = 1;
                if( l_cnt > max_non)
                    l_cnt = max_non;
                
                r_cnt += (  rand() % 3 - 1);
                if( r_cnt < 1 )
                    r_cnt = 1;
                if( r_cnt > max_non)
                    r_cnt = max_non;
                
                log( "l_cnt ? %i , r_cnt ? %i " , l_cnt , r_cnt);
                
                if( player_pos_y == v_idx )
                {
                    int dealt_cnt = ( h_cnt - r_cnt - l_cnt - 2 );
                    player_pos_x = (l_cnt + 1 + rand() % dealt_cnt);
                    
                    log( "grene player_pos_x ! dealt_cnt ? %i (%i,%i)", dealt_cnt , player_pos_x , player_pos_y);
                }
            }
            
            //fill Left
            for( int l_idx = 0 ; l_idx < h_cnt ; l_idx++ ){
                floor_plan[ v_idx * h_cnt + l_idx ] = BlockType::Non;
                if( l_idx > l_cnt ){ // wall on the last
                    
                    if( v_idx == 0 || v_idx == v_cnt - 1 ){
                        // fill wall, be close the map
                        floor_plan[ v_idx * h_cnt + l_idx ] = BlockType::Wall;
                    }else{
                        if( l_idx - l_cnt == 1 ){
                            //Set to Wall to block the player wall over the area
                            floor_plan[ v_idx * h_cnt + l_idx ] = BlockType::Wall;
                        }else{
                            //Set To Floor for player walk
                            floor_plan[ v_idx * h_cnt + l_idx ] = BlockType::Floor;
                            
                            if( player_pos_y == v_idx && player_pos_x == l_idx && player_pos == Vec2::ZERO){
                                if(true)
                                {
                                    //set the block to Player
                                    floor_plan[ v_idx * h_cnt + l_idx ] = BlockType::Player;
                                }
                            }
                        }
                    }
                }
            }
            
            //fill Left
            for( int r_idx = (h_cnt - r_cnt) ; r_idx < h_cnt ; r_idx++ ){
                floor_plan[ v_idx * h_cnt + r_idx ] = BlockType::Non;
                
//                log( "grene right wall :: r_idx ? %i " , r_idx);
                if( r_idx == h_cnt - 1){ // wall on the last
                    floor_plan[ v_idx * h_cnt + (h_cnt - r_cnt - 1) ] = BlockType::Wall;
//                    log( "grene right wall !");
                }
            }
            
        }
        
        //after the layout grant,
        //get the map
        
        for(int w_idx = 0 ; w_idx < total_cnt ; w_idx ++ )
        {
            //calcu a new pos for each block
            auto n_pos = Vec2( (w_idx % h_cnt), (int)(w_idx / h_cnt));
            
            //Case where do plast the wall
            switch( floor_plan[w_idx] ){
                case BlockType::Non :
                    CreateFloor("res/map/Grass_01.jpg" , n_pos);
                    break;
                case BlockType::Wall :
                    CreateWall(res_path_ground , n_pos , categoryBit , collisionBitmask , contactTestBitmask);
                    break;
                case  BlockType::Floor :
                    CreateFloor(res_path_ground , n_pos);
                    break;
                case BlockType::Player :
                    {
                        auto sp = CreateFloor("res/heart_64.png" , n_pos);
                        player_pos = sp->getPosition();
                        
                        //set n_pos for public get;
                        log( "grene player ! final_pos (%f , %f)" , player_pos.x, player_pos.y);
                    }
                    break;
                case BlockType::Enemry :
                    CreateFloor(res_path_ground , n_pos);
                    break;
            }
        }
    }

    
    //TODO :: Monster Position
    //TODO :: Block Position
    //TODO :: Item Position
    
}


