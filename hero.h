#ifndef HERO_H
#define HERO_H

#include <QPoint>
#include <trajectory.h>
class Hero
{
public:
    Hero();
    void SetHero(int num, QPointF pos){NumberOfLives=num; position=pos;};
    int NumberOfLives;
    int bullets=0;
    QPointF position;
    Trajectory trajectory;
};

#endif // HERO_H
