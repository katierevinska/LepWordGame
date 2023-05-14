#ifndef BULLET_H
#define BULLET_H
#include <QPointF>
#include <trajectory.h>
#include<QDebug>
class Bullet
{
public:
    Bullet(QPointF position_):position(position_){
 trajectory.setTrajectory({position_,{position_.rx()+100,position_.ry()}},"Bullet");

    };
    QPointF position;
    int num=1;
    Trajectory trajectory;
};

#endif // BULLET_H
