#ifndef MODEL_H
#define MODEL_H
#include "hero.h"
#include "map.h"
#include <vector>
#include <QString>
#include <QPointF>
class Model
{
public:
    ~Model(){};
    Hero hero;
    std::vector<Bullet> flyingBullets={};
    std::vector<Map> maps;
    Map currentMap;
    int gold=0;
    void SetModelByLevel(int level);
    void changeEnemiesPosition();
    void changeFlyingBulletsPosition();
    void createFlyingBullet(QPointF, QString, int);
    void moveHeroEvent(int);
};

#endif // MODEL_H
