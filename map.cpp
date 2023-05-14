#include "map.h"
#include <QDebug>
void Map::setMap(std::vector<QPointF> way_,std::vector<Enemy> enemies_,std::vector<coint> coints_){
    way = way_;
    enemies = enemies_;
    coints = coints_;
}
