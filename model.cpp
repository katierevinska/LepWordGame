#include "model.h"
#include<QDebug>
void Model::SetModelByLevel(int level){
    if(level==1){
        std::vector<QPointF> way={{0,150},{450, 150}};
        hero.SetHero(1, {way[0].x()+5, way[0].y()});
        std::vector<Enemy> enemies={{1,{{75,way[0].y()},{120, way[0].y()}}, Enemy::Bee},{1,{{200,way[0].y()},{240, way[0].y()}}, Enemy::Bee}};
        std::vector<coint> coints={{{60, 100}},{{120,100}}};
        currentMap.setMap(way,enemies,coints);//currentMap=maps[0]

    }
};
void Model::changeEnemiesPosition(){
    for(auto &enemy: currentMap.enemies){

        enemy.position=enemy.trajectory.positionByTrajectory().second;
    }
};
