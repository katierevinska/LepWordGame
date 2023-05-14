#include "model.h"
#include<QDebug>
void Model::SetModelByLevel(int level){
    if(level==1){
        hero.SetHero(1, {20, 60});
        std::vector<QPoint> way={{0,60},{160, 60}};
        std::vector<Enemy> enemies={{1,{{100,60},{160, 60}}, Enemy::Bee}};
        std::vector<coint> coints={{{60, 60}}};
        currentMap.setMap(way,enemies,coints);//currentMap=maps[0]
    }
};
void Model::changeEnemiesPosition(){
    for(auto &enemy: currentMap.enemies){
        int posX = enemy.moveWay[0].rx()+(enemy.position.rx()-enemy.moveWay[0].rx()+20)%(enemy.moveWay[1].rx()-enemy.moveWay[0].rx());
        enemy.position.rx()=posX;
    }
};
