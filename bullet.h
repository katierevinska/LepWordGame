#ifndef BULLET_H
#define BULLET_H
#include <QPointF>
#include <trajectory.h>
#include<QDebug>
class Bullet
{
public:
    enum TypeOfBullet{
        ForKillHero, ForKillEnemy
    };
    Bullet(QPointF position_):position(position_){};
    Bullet(QPointF position_, QString type):position(position_){
        if(type == "forKillHero"){
            bulletType = ForKillHero;
        }else{
            bulletType = ForKillEnemy;
        }
        trajectory.setTrajectory({position_,"Attack"});
    };
    QPointF position;
    TypeOfBullet bulletType;
    int num=1;
    Trajectory trajectory;
};

#endif // BULLET_H
