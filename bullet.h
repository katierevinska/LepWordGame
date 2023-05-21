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
    Bullet(QPointF position_, QString type, int direction):position(position_){
        if(type == "forKillHero"){
            bulletType = ForKillHero;
        }else{
            bulletType = ForKillEnemy;
        }
        if(direction==1){
            trajectory.setTrajectory({position_,"RAttack"});
        }else{
            trajectory.setTrajectory({position_,"LAttack"});
        }

    };
    QPointF position;
    TypeOfBullet bulletType;
    int num=1;
    Trajectory trajectory;
};

#endif // BULLET_H
