#include "map.h"
//#include <QDebug>
void Map::setMap(std::vector<Road> way_,std::vector<Enemy> enemies_,std::vector<coint> coints_, std::vector<Bullet> bullets_){
    way=way_;
enemies = enemies_;
    coints = coints_;
    bullets = bullets_;
    qDebug()<<"end setcurrent Map";
}
