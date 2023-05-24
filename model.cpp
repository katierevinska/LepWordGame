#include "model.h"
#include <QPolygonF>

void Model::SetModelByLevel(int level){
    if(level==1){
        std::vector<QPolygonF> way={{{{0,600},{1500, 600},{1500, 800},{0, 800}}},{{{70,520},{240,520},{240,545},{70,545}}}};
        hero.SetHero(3, {way[0].first().rx()+10, way[0].first().ry()-8});
        qDebug()<<hero.position;
        std::vector<Enemy> enemies={{1,{{75,596},{120, 596}}, Enemy::Bee},
                                    {1,{{350,596},{450, 596}}, Enemy::Bee},
                                    {1,{{800,596},{930, 596}}, Enemy::Troll}};
        std::vector<coint> coints={{{60,530}},{{120,530}}};

        std::vector<Bullet> bullets={{{220, 530}},{{290,530}}};
                currentMap.setMap(way,enemies,coints,bullets);//currentMap=maps[0]
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
