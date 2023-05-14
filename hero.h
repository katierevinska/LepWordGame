#ifndef HERO_H
#define HERO_H

#include <QPoint>

class Hero
{
public:
    Hero(){};
    void SetHero(int num, QPoint pos){NumberOfLives=num; position=pos;};
    int NumberOfLives;
    QPoint position;
};

#endif // HERO_H
