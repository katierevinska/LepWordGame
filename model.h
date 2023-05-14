#ifndef MODEL_H
#define MODEL_H
#include "hero.h"
#include "map.h"
#include <vector>
#include <QString>
class Model
{
public:
    Model(){};//два конструктора на один объект?
    Hero hero;
    std::vector<Bullet> flyingBullets={};
    std::vector<Map> maps;
    Map currentMap;
    int gold=0;
    ~Model(){};
    void SetModelByLevel(int level);
    void changeEnemiesPosition();
    void changeFlyingBulletsPosition();
    void createFlyingBullet(QPointF);
    void moveHeroEvent(int);
};

#endif // MODEL_H
