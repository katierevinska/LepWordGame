#include "model.h"
#include <QPolygonF>

void Model::SetModelByLevel(int level){
    if(level==1){
       std::vector<Road> way={{{0,650},Road::Ground},{{250,650},Road::Ground},
                                     {{500,650},Road::Ground},
                                     {{750,650},Road::Ground},
                                     {{1000,650},Road::Ground},
                                     {{1250,650},Road::Ground},
                              {{1500,650},Road::Ground},
                              {{1750,650},Road::Ground},
                                    {{70,510},Road::Block},
                             {{115,510},Road::Block},
                             {{160,510},Road::Block},
                              {{400,510},Road::Block},
                       {{445,510},Road::Block},
                       {{490,510},Road::Block}};
        hero.SetHero(3, {way[0].polygon[0].x()+10, way[0].polygon[0].y()-8});
        std::vector<Enemy> enemies={{1,{{75,596},{120, 596}}, Enemy::Bee},
                                    {1,{{350,596},{450, 596}}, Enemy::Bee},
                                    {1,{{800,596},{930, 596}}, Enemy::Troll}};
        std::vector<coint> coints={{{150,470}},{{450,470}},{{200,610}},{{500,610}}};

        std::vector<Bullet> bullets={/*{{220, 530}},{{290,530}}*/};
    qDebug()<<"set current map";
                currentMap.setMap(way,enemies,coints,bullets);//currentMap=maps[0]
    qDebug()<<"already set current map";
    }
};
void Model::createFlyingBullet(QPointF pos, QString type, int direction){
    flyingBullets.push_back({pos, type,direction});
}

void Model::changeEnemiesPosition(){
    for(auto &enemy: currentMap.enemies){
        enemy.position=enemy.trajectory.positionByTrajectory().second;
    }
};
void Model::changeFlyingBulletsPosition(){
   // for(auto &bullet: flyingBullets){
    int i =0;

    while(i<=(int)flyingBullets.size()-1){
        flyingBullets[i].position=flyingBullets[i].trajectory.positionByTime().second;

        if(flyingBullets[i].trajectory.positionByTime().first==Trajectory::No){
            flyingBullets.erase(flyingBullets.begin()+i);
        }else{
            i++;
        }
    }
};
