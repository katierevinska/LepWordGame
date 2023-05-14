#ifndef ENEMY_H
#define ENEMY_H

#include <QPoint>
#include <QPair>
#include <vector>
class Enemy
{
public:
    enum ClassType {
        Snail, Bee
    };
    Enemy(){}
    Enemy(int num, std::vector<QPoint> moveWay_, ClassType name_):
        NumOfAttackForDeath(num),moveWay(moveWay_),name(name_){
        position = moveWay[0];
    };

    int NumOfAttackForDeath;
    std::vector<QPoint> moveWay;
    QPoint position;
    ClassType name;
};

#endif // ENEMY_H
