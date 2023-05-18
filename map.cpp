#include "map.h"
#include "qpolygon.h"
//#include <QDebug>
void Map::setMap(std::vector<QPolygonF> way_,std::vector<Enemy> enemies_,std::vector<coint> coints_, std::vector<Bullet> bullets_){
    way = way_;
    enemies = enemies_;
    coints = coints_;
    bullets = bullets_;
}
