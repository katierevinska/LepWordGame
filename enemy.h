#ifndef ENEMY_H
#define ENEMY_H

#include <QPoint>
#include <QPair>
#include <QDebug>

#include <vector>
#include <trajectory.h>
class Enemy
{
public:
    enum ClassType {
        Snail, Bee
    };
    Enemy(){}
    Trajectory trajectory;
    Enemy(int num, std::vector<QPointF> moveWay_, ClassType name_){
        NumOfAttackForDeath=num;
        trajectory.setTrajectory(moveWay_, "Bee");
        name=name_;
        position = moveWay_[0];
    };

    int NumOfAttackForDeath;
    QPointF position;
    ClassType name;
};

#endif // ENEMY_H
