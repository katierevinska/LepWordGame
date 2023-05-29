#ifndef ENEMY_H
#define ENEMY_H

#include <QPointF>
#include <QPair>


#include <vector>
#include <trajectory.h>
class Enemy
{
public:
    enum ClassType {
        Snail, Bee, Troll
    };
    Enemy(){}
    Trajectory trajectory;
    Enemy(int num, std::vector<QPointF> moveWay_, ClassType name_){
        NumOfAttackForDeath=num;
        if(name_==Snail)
        trajectory.setTrajectory(moveWay_, "Snail");
        if(name_==Troll)
        trajectory.setTrajectory(moveWay_, "Troll");
        if(name_==Bee)
        trajectory.setTrajectory(moveWay_, "Bee");
        name=name_;
        position = moveWay_[0];
    };
    int NumOfAttackForDeath;
    QPointF position;
    ClassType name;
};

#endif // ENEMY_H
