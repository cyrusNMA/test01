//
//  Charactor.hpp
//  test01
//
//  Created by cyruslam on 20/12/15.
//
//

#ifndef Charactor_h
#define Charactor_h

#include "cocos2d.h"

class GameObject : public cocos2d::Node
{
    public :
    int hp = 0 ;
    int speed = 0;
    int attack = 0;
};

class Charactor : public GameObject
{
    protected :
    float eachMoveDuration_long = 500;
    float attackFeq = 0.5;
    bool ableToFire = false;
    
    public :
    
    void SetBody( std::string res_path ){
        //TODO 
        auto body = cocos2d::DrawNode::create();
        body->setName("body");
        body->drawSolidRect(cocos2d::Vec2(0,0), cocos2d::Vec2(10,25), cocos2d::Color4F(0.1, 0, 1, 1));
        this->addChild(body);
    }
    
    void SetAttackFeq(float n_feq){
        attackFeq = n_feq;
        //Stop on running schedule
        this->unschedule(schedule_selector(Charactor::ScheduleAttackHandle));
        //reset the schedule
        this->schedule(schedule_selector(Charactor::ScheduleAttackHandle), attackFeq);
    }
    
    void Fire( cocos2d::Scene *scene , cocos2d::Vec2 targetPos)
    {
        
        //create bullet
        auto n_bullet = EmitOneBullet(targetPos);
        
        //add to scene for drawing
        scene->addChild(n_bullet);
    }
    
    cocos2d::Node* EmitOneBullet(cocos2d::Vec2 targetPos)
    {
        //create bullet
        if( !ableToFire )
            return nullptr;
        else
            ableToFire = false;
        
        cocos2d::log("return bullet");
        
        auto n_bullet = cocos2d::DrawNode::create();
        n_bullet->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(10, 10), cocos2d::Color4F(1,1,1,1));
//        this->addChild(n_bullet);
        
        //init pos
        n_bullet->setPosition(this->getPosition());
        
        //set target position
        auto actionMove = cocos2d::MoveTo::create(GetDest(this->getPosition() ,targetPos)/eachMoveDuration_long, targetPos);
        auto actionRemove = cocos2d::RemoveSelf::create();
        n_bullet->runAction(cocos2d::Sequence::create(actionMove, actionRemove, nullptr));
        
        return n_bullet;
    }
    
    double GetDest( cocos2d::Vec2 pos_1 , cocos2d::Vec2 pos_2 ){
        
        auto dest = std::sqrt(std::pow(pos_1.x - pos_2.x, 2) + std::pow(pos_1.y - pos_2.y, 2));
        
        return dest;
    }
    
    void MoveToPos(cocos2d::Vec2 n_pos)
    {
        //    Vec2 offset = touchLocation - _player->getPosition();
        int speed_to_time = speed * 10;
        if( speed > 0 ){
            
            auto dest = std::sqrt(std::pow(this->getPositionX() - n_pos.x, 2) + std::pow(this->getPositionY() - n_pos.y, 2));
            
            auto actionMove = cocos2d::MoveTo::create(dest/speed_to_time, n_pos);
            this->stopAllActions();
            this->runAction(cocos2d::Sequence::create(actionMove, nullptr));
        }else{
            cocos2d::MessageBox("player speed is 0","Alert");
        }
    }
    
    void MoveWithDirection( cocos2d::Vec2 n_pos )
    {
        
    }
    
    //****** Callback ******
    void ScheduleAttackHandle(float dt)
    {
//        cocos2d::log( "Charactor::ScheduleAttackHandle() called !" );
        if( !ableToFire ){
            ableToFire = true;
        }
    }
};

class Player : public Charactor
{
    
};

class Enemy : public Charactor
{
    
};

#endif /* Charactor_h */
