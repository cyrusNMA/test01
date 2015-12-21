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
    int hp;
    int speed;
    int attack;
};

class Charactor : public GameObject
{
    protected :
    float eachMoveDuration_long = 100;
    float attackFeq = 0.5;
    
    public :
    
    void SetAttackFeq(float n_feq){
        attackFeq = n_feq;
    }
    
    void Fire( cocos2d::Scene *scene , cocos2d::Vec2 targetPos){
        
        //create bullet
        auto n_bullet = EmitOneBullet(targetPos);
        
        //add to scene for drawing
        scene->addChild(n_bullet);
    }
    
    cocos2d::Node* EmitOneBullet(cocos2d::Vec2 targetPos){
        //create bullet
        auto n_bullet = cocos2d::DrawNode::create();
        n_bullet->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(10, 10), cocos2d::Color4F(1,0.5,0,1));
        
        //init pos
        n_bullet->setPosition(this->getPosition());
        
        //set target position
        
        auto actionMove = cocos2d::MoveTo::create(GetDest(this->getPosition() ,targetPos)/eachMoveDuration_long, targetPos);
        n_bullet->runAction(cocos2d::Sequence::create(actionMove, nullptr));
        
        return n_bullet;
    }
    
    double GetDest( cocos2d::Vec2 pos_1 , cocos2d::Vec2 pos_2 ){
        
        auto dest = std::sqrt(std::pow(pos_1.x - pos_2.x, 2) + std::pow(pos_1.y - pos_2.y, 2));
        
        return dest;
    }
};

class Player : public Charactor
{
    
};

class Enemy : public Charactor
{
    
};

#endif /* Charactor_h */
