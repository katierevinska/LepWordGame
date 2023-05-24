#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "enemy.h"
#include "coint.h"
#include "bullet.h"
class Map
{
public:
    void setMap(std::vector<QPolygonF> way_,std::vector<Enemy> enemies_,std::vector<coint> coints_, std::vector<Bullet> bullets_);
    Map(){};
    std::vector<QPolygonF> way;
    std::vector<Enemy> enemies;
    std::vector<coint> coints;
    std::vector<Bullet> bullets;
};

#endif // MAP_H
