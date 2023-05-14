#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QPoint>
#include "enemy.h"
#include "coint.h"
class Map
{
public:
    void setMap(std::vector<QPoint> way_,std::vector<Enemy> enemies_,std::vector<coint> coints_);
    Map(){
        way.push_back({});
         way.push_back({});
         enemies.push_back({});
    };
    std::vector<QPoint> way;

    std::vector<Enemy> enemies;
    std::vector<coint> coints;
};

#endif // MAP_H
