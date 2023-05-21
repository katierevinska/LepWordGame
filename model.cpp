#include "model.h"
#include <QPolygonF>

void Model::SetModelByLevel(int level){
    if(level==1){
        std::vector<QPolygonF> way={{{{0,150},{800, 150},{800, 200},{0, 200}}}};
        hero.SetHero(3, {way[0].first().rx()+5, way[0].first().ry()-7});
        qDebug()<<hero.position;
        std::vector<Enemy> enemies={{1,{{75,146},{120, 146}}, Enemy::Bee},
                                    {1,{{200,146},{240, 146}}, Enemy::Bee},
                                    {1,{{420,146},{520, 146}}, Enemy::Troll}};
        std::vector<coint> coints={{{60, 100}},{{120,100}}};

        std::vector<Bullet> bullets={{{55, 110}},{{110,100}}};
                currentMap.setMap(way,enemies,coints,bullets);//currentMap=maps[0]
 }
};
void Model::createFlyingBullet(QPointF pos, QString type){
    flyingBullets.push_back({pos, type});
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
