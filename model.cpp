#include "model.h"
#include <QPolygonF>

void Model::SetModelByLevel(int level){
    if(level==1){
        std::vector<Road> way={{{0,650},Road::Ground},
                               {{250,650},Road::Ground},
                               {{500,650},Road::Ground},
                               {{750,650},Road::Ground},
                               {{1000,650},Road::Ground},
                               {{1250,650},Road::Ground},
                               {{1500,650},Road::Ground},
                               {{1750,650},Road::Ground},

                               {{2000,650},Road::Ground},
                               {{2250,650},Road::Ground},
                               {{2500,650},Road::Ground},
                               {{2750,650},Road::Ground},
                               {{3000,650},Road::Ground},
                               {{3250,650},Road::Ground},
                               //{{3500,650},Road::Ground},
                               {{3750,650},Road::Ground},

                               {{4000,650},Road::Ground},
                               {{4250,650},Road::Ground},
                               {{4500,650},Road::Ground},
                               {{4750,650},Road::Ground},
                               {{5000,650},Road::Ground},
                               {{5250,650},Road::Ground},
                               {{5500,650},Road::Ground},
                               {{5750,650},Road::Ground},


                               {{400,490},Road::Block},
                               {{445,490},Road::Block},
                               {{490,490},Road::Block},

                               {{670,490},Road::Block},
                               {{715,490},Road::Block},
                               {{760,490},Road::Block},

                               {{1430,490},Road::Block},
                               {{1475,490},Road::Block},
                               {{1520,490},Road::Block},

                               {{2070,490},Road::Block},
                               {{2115,490},Road::Block},
                               {{2160,490},Road::Block},

                               {{2265,415},Road::Block},
                               {{2310,415},Road::Block},
                               {{2355,415},Road::Block},

                               {{2460,490},Road::Block},
                               {{2505,490},Road::Block},
                               {{2550,490},Road::Block},
                              };
        hero.SetHero(3, {way[0].polygon[0].x()+10, way[0].polygon[0].y()-8});
        std::vector<Enemy> enemies={{1,{{830,596},{930, 596}}, Enemy::Snail},
                                    {1,{{1100,596},{1130, 596}}, Enemy::Snail},
                                    {1,{{1300,596},{1400, 596}}, Enemy::Snail},
                                    {1,{{1520,596},{1650, 596}}, Enemy::Snail},
                                    {3,{{3900,596},{4250, 596}}, Enemy::Troll},
                                    {1,{{2600,250},{2600, 600}}, Enemy::Bee},
                                    {1,{{540,250},{540, 600}}, Enemy::Bee},
                                    {1,{{4700,250},{4700, 600}}, Enemy::Bee}
                                   };
        std::vector<coint> coints={{{150,460},coint::Coint},
                                   {{450,460},coint::Coint},
                                   {{200,610},coint::Coint},
                                   {{500,610},coint::Coint},
                                    {{740,610},coint::Coint},
                                    {{1100,610},coint::Coint},
                                    {{1400,610},coint::Coint},
                                   {{1430,390},coint::Coint},
                                   {{1470,390},coint::Coint},

                                    {{1900,610},coint::Coint},
                                    {{2250,380},coint::Coint},
                                   {{2310,380},coint::Coint},
                                   {{2370,380},coint::Coint},
                                   {{4300,610},coint::Coint},
                                   {{4360,610},coint::Coint},
                                   {{4420,610},coint::Coint},

                                  {{5200,545},coint::Pot}};

        std::vector<Bullet> bullets={{{220, 530}},{{290,530}}};
        currentMap.setMap(way,enemies,coints,bullets);//currentMap=maps[0]

        qDebug()<<"set current map";
    }else if(level==2){
        qDebug()<<"2l";
            std::vector<Road> way={{{0,650},Road::Ground},
                                   {{250,650},Road::Ground},
                                   {{500,650},Road::Ground},
                                   {{750,650},Road::Ground},
                                   {{1000,650},Road::Ground},
                                   {{1250,650},Road::Ground},
                                   {{1500,650},Road::Ground},
                                   {{1750,650},Road::Ground},

//                                   {{2000,650},Road::Ground},
//                                   {{2250,650},Road::Ground},
//                                   {{2500,650},Road::Ground},
                                   {{2750,650},Road::Ground},
                                   {{3000,650},Road::Ground},
                                   {{3250,650},Road::Ground},
                                   {{3500,650},Road::Ground},
                                   {{3750,650},Road::Ground},

                                   {{4000,650},Road::Ground},
                                   {{4250,650},Road::Ground},
                                   {{4500,650},Road::Ground},
                                   {{4750,650},Road::Ground},
                                   //{{5000,650},Road::Ground},
                                   {{5250,650},Road::Ground},
                                   {{5500,650},Road::Ground},
                                   {{5750,650},Road::Ground},

                                   {{1650,490},Road::Block},
                                   {{1685,490},Road::Block},
                                   {{1730,490},Road::Block},

                                   {{1830,425},Road::Block},
                                   {{1875,425},Road::Block},
                                   {{1920,425},Road::Block},

//                                   {{2180,380},Road::Block},
//                                   {{2225,380},Road::Block},
//                                   {{2270,380},Road::Block},
//---------
                                   {{2080,490},Road::Block},
                                   {{2125,490},Road::Block},
                                   {{2170,490},Road::Block},

                                   {{2275,385},Road::Block},
                                   {{2320,385},Road::Block},
                                   {{2365,385},Road::Block},

                                   {{2470,490},Road::Block},
                                   {{2515,490},Road::Block},
                                   {{2560,490},Road::Block},

                                   {{5050,450},Road::Block},
                                   {{5095,450},Road::Block},
                                   {{5140,450},Road::Block},
                                   {{5185,450},Road::Block},
                                   };
            hero.SetHero(3, {way[0].polygon[0].x()+10, way[0].polygon[0].y()-8});
            std::vector<Enemy> enemies={/*{1,{{830,596},{930, 596}}, Enemy::Snail},
                                        {1,{{1100,596},{1130, 596}}, Enemy::Snail},
                                        {1,{{1300,596},{1400, 596}}, Enemy::Snail},
                                        {1,{{1520,596},{1650, 596}}, Enemy::Snail},*/
                                        {1,{{1100,596},{1520, 596}}, Enemy::Troll},
                                        {1,{{3000,596},{3550, 596}}, Enemy::Troll},
                                        {3,{{3700,596},{4350, 596}}, Enemy::Troll},
                                        {1,{{2600,250},{2600, 600}}, Enemy::Bee},
                                        {1,{{540,250},{540, 600}}, Enemy::Bee},
                                        {1,{{680,250},{680, 600}}, Enemy::Bee},
                                        {1,{{4700,250},{4700, 600}}, Enemy::Bee},
                                        {1,{{4800,250},{4800, 600}}, Enemy::Bee},
                                        {1,{{4900,250},{4900, 600}}, Enemy::Bee}
                                       };
            std::vector<coint> coints={{{150,460},coint::Coint},
                                       {{450,460},coint::Coint},
                                       {{200,610},coint::Coint},
                                       {{500,610},coint::Coint},
                                        {{740,610},coint::Coint},
                                        {{1100,610},coint::Coint},
                                        {{1400,610},coint::Coint},
                                       {{1430,390},coint::Coint},
                                       {{1470,390},coint::Coint},

                                        {{1900,610},coint::Coint},
                                        {{2250,380},coint::Coint},
                                       {{2310,380},coint::Coint},
                                       {{2370,380},coint::Coint},
                                       {{4300,610},coint::Coint},
                                       {{4360,610},coint::Coint},
                                       {{4420,610},coint::Coint},

                                      {{5100,340},coint::Pot}};

            std::vector<Bullet> bullets={{{220, 530}},{{290,530}}};
            currentMap.setMap(way,enemies,coints,bullets);//currentMap=maps[0]

            qDebug()<<"set current map";
        }
        qDebug()<<"already set current map";

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
