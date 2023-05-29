#include "presenter.h"
#include "ui_firstmenu.h"
#include "view.h"
#include<QObject>
#include <cmath>

Presenter::Presenter():
    menu(new FirstMenu(this)),
    view_(std::make_unique<View>(this)),
    model_(std::make_unique<Model>()) {
    //view_->show();
//    menu->show();
menu->ui->label->setVisible(false);
    menu->showFullScreen();
    timer = new QTimer(this);
    MainTimer = new QTimer(this);
    timerForAttack = new QTimer(this);
    immortalityForHero = new QTimer(this);
    //connect(menu_->start, &QPushButton::clicked, this, [this]{startGame(1);});
    connect( MainTimer, &QTimer::timeout, this, &Presenter::timerEvent);
    connect( timer, &QTimer::timeout, this, &Presenter::moveTimeHero);
    connect( timerForAttack, &QTimer::timeout, this, &Presenter::creatingAttac);
    connect( immortalityForHero, &QTimer::timeout, this, [this]{immortalityForHero->stop();
        view_->changeToHealthy();});
    connect(menu->ui->start, &QPushButton::clicked, this, [this] {
        if(menu->ui->level1->isChecked()){startGame(1);}
    else if (menu->ui->level2->isChecked()){startGame(2);}
    });

}
void Presenter::moveEvents(QString str){
    if(str=="Attack"){
        if(model_->hero.bullets>0){

            model_->createFlyingBullet({{(int)model_->hero.position.x(),(int)model_->hero.position.y()-30}},"forKillEnemy",model_->hero.trajectory.flagDirection);
            model_->hero.bullets--;
        }
    }else{
        if(timer->isActive()){
            timer->stop();
        }
        timer->start(10);

        model_->hero.trajectory.setTrajectory({model_->hero.position,str});
    }

}
void Presenter::moveTimeHero(){
    double X_ = model_->hero.position.x();
    QPair<Trajectory::End_,QPointF> pair = model_->hero.trajectory.positionByTime();
    auto typeTraj = model_->hero.trajectory.typeOfTrajectory;

    if(typeTraj ==Trajectory::Up ||typeTraj ==Trajectory::Right ||
            typeTraj ==Trajectory::Left ){//значит герой
        if(calcRoad(pair.second).first ==Presenter::DownHorizontalRoad){

            model_->hero.trajectory.stopByDownHorizontalRoad();
            //timer->stop();
        }else if(calcRoad(pair.second).first ==Presenter::UpHorizontalRoad){

            model_->hero.trajectory.stopByUpHorizontalRoad();
            //timer->stop();
        }else
        if(calcRoad(pair.second)/*может сказать поменять траекторию
        вернёт новую позицию зная дорогу*/.first ==Presenter::VerticalRoad){
            model_->hero.trajectory.stopByVerticalRoad();
        }//узнаём мешает ли дорога и затем ставим вычисленную позицию.
//    }/*else*/
        if(calcRoad(pair.second)/*может сказать поменять траекторию
        вернёт новую позицию зная дорогу*/.first ==Presenter::Nothing){
            //moveEvents("Up");
            qDebug()<<"with-----------------------";
            model_->hero.trajectory.withoutRoad();

            timer->start(10);
            //qDebug()<<
        }
        model_->hero.position = calcRoad(pair.second).second;
        if(model_->hero.position.x()>view_->width()/2&&model_->hero.position.x()<view_->width()*3-view_->width()/2)
view_->p_x-=model_->hero.position.x()-X_;

        //изменить новую траекторию если данная не подходит
    if(pair.first==Trajectory::No){//остановка->|//уже посчитана конечная позиция
    // остановить скорость героя, если траекторию уже не изменили по вычисленному столкновению
               //Например через
                //model_->hero.trajectory.stopByHorizontalRoad();//stop how horizontal if -> \ <-
               //, if bullet -delete traj
        model_->hero.trajectory.V_x=0;
        model_->hero.trajectory.typeOfTrajectory=Trajectory::Not;
qDebug()<<"stoping";
        timer->stop();
    }}
}
void Presenter::startGame(int numLeven){
    menu->hide();
    view_->showFullScreen();
    setLevel(numLeven);
        code = Go;
   MainTimer->start(20);
    timerForAttack->start(700);

}
void Presenter::setLevel(int level){
    qDebug()<<"start of set level";
        model_->SetModelByLevel(level);
            qDebug()<<"already set by level";
view_->p_x=0;
model_->hero.trajectory.typeOfTrajectory=Trajectory::Not;
model_->hero.trajectory.a_=0;
model_->hero.trajectory.V_x=0;
model_->hero.bullets=10;
}
void Presenter::timerEvent(){
    model_->changeEnemiesPosition();
    model_->changeFlyingBulletsPosition();
    changeData(calculateEvent());
    view_->update();
}

void Presenter::changeData(QPair<Presenter::EventType, int> eventPair){

     if(eventPair.first==Presenter::Killing||eventPair.first==Presenter::Enemy||model_->hero.position.y()>800){
       if(model_->hero.position.y()>800){
         model_->hero.NumberOfLives=0;
       }else{
        model_->hero.NumberOfLives--;
       }

        if(model_->hero.NumberOfLives==0){
            code=Fail;
            GameOver();
        }else{
            minusLifeOfHero();
        }

    }
    if(eventPair.first==Presenter::Attac){
        model_->currentMap.enemies[eventPair.second].NumOfAttackForDeath--;
        if(model_->currentMap.enemies[eventPair.second].NumOfAttackForDeath==0){
            model_->currentMap.enemies.erase(model_->currentMap.enemies.begin()
                                             +eventPair.second);
        }
    }
    if(eventPair.first==Presenter::Coint){
        model_->gold+=model_->currentMap.coints[eventPair.second].NumOfGold;
        model_->currentMap.coints.erase(model_->currentMap.coints.begin()+eventPair.second);
    }
    if(eventPair.first==Presenter::Bullet){
        model_->hero.bullets+=model_->currentMap.bullets[eventPair.second].num;
        model_->currentMap.bullets.erase(model_->currentMap.bullets.begin()+eventPair.second);
    }
}
QPair<Presenter::EventType, QPointF> Presenter::calcRoad(QPointF posForCheck){
//    if(model_->hero.position.ry()>800){
//        code=Fail;
//        GameOver();
//        return{Failing,{}};
//    }
    QPolygonF hero({{posForCheck.x()-30,posForCheck.y()-93},
                    {posForCheck.x()+30,posForCheck.y()-93},
                    {posForCheck.x()+30,posForCheck.y()+8},
                    {posForCheck.x()-30,posForCheck.y()+8}});
    for(auto road:model_->currentMap.way){
        if(road.polygon.intersects(hero)){
            for(int i = 0; i < road.polygon.size(); ++i){
                double s_py=road.polygon[i].ry();
                double s_px=road.polygon[i].rx();
                double s_dx=road.polygon[(i+1)%(int)(road.polygon.size())].rx()-s_px;
                double s_dy=road.polygon[(i+1)%(int)(road.polygon.size())].ry()-s_py;
                if(s_dy==0){
                    double T1 = (s_py-posForCheck.y())/8;
                    double T2 = (posForCheck.x()-s_px)/s_dx;
                if(0<=T2&&T2<=1 /*&& T1>=-1&&T1<=1*/){
                    if( T1>=0 && T1<=1){

                    posForCheck={posForCheck.x(), posForCheck.y()-(1-T1)*8};
                    return {Presenter::DownHorizontalRoad, posForCheck};
                    }else {
                        T1 = (s_py-posForCheck.y())/55;
                        if( T1>=-1&&T1<=0){

                        posForCheck={posForCheck.x(), posForCheck.y()
                                     +(T1+1)*55};
                        return {Presenter::UpHorizontalRoad, posForCheck};
                        }
                    }
                }

                }
                else if(s_dx==0){
                  double  T1 = (s_px-posForCheck.x())/30;
                  double  T2 = (posForCheck.y()-s_py)/s_dy;
   /// qDebug()<<model_->hero.position <<"road"<<road[i]<<road[(i+1)%(int)(road.size())]<<"t"<<T1<<T2;
                    if(0<=T2&&T2<=1){//слева/справа
                        if(T1>=0 && T1<=1){
                        posForCheck={posForCheck.x()-(1-T1)*30, posForCheck.y()};
                       return {Presenter::VerticalRoad, posForCheck};
                        }else if(T1<=0 && T1>=-1){
                            posForCheck={posForCheck.x()+(1+T1)*30, posForCheck.y()};
                           return {Presenter::VerticalRoad, posForCheck};
                            }


                    }
                }
                //if(model_->currentMap.way[0].contains(model_->hero.position)){
            }
            //x
        }
    }

    return{Presenter::Nothing, posForCheck};
}
QPair<bool,int> Presenter::calculateKillingEnemy(QPointF position){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
        if(abs(model_->currentMap.enemies[i].position.x()-position.x())<15&&
                abs(model_->currentMap.enemies[i].position.y()-position.y())<50){
            return {true,i};
        }
    }
    return {false,-1};
}
bool Presenter::calculateKillingHeroByBullets(QPointF position){
    if(abs(position.x()-model_->hero.position.x())<15&&
               abs(model_->hero.position.y()-position.y())<50){
        return true;
    }
    return false;
}
QPair<bool,int> Presenter::calculateKillingHero(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
        if(!(immortalityForHero->isActive()) && abs(model_->hero.position.y()-model_->currentMap.enemies[i].position.y())<50&&
                                                     abs(model_->hero.position.x()-model_->currentMap.enemies[i].position.x())<30){
            return {true,i};
        }
    }
    return {false,-1};
}
QPair<bool,int> Presenter::calculateCoints(){
    for(int i = 0; i < model_->currentMap.coints.size();i++){
        if(model_->currentMap.coints[i].typeOfGold != coint::Pot&&sqrt(pow(model_->hero.position.x()-model_->currentMap.coints[i].position.x(),2)
                +pow(model_->hero.position.y()-model_->currentMap.coints[i].position.y(),2))<60
                ){
            return {true,i};}
        else if(model_->currentMap.coints[i].typeOfGold == coint::Pot&&sqrt(pow(model_->hero.position.x()-model_->currentMap.coints[i].position.x(),2)
                     +pow(model_->hero.position.y()-model_->currentMap.coints[i].position.y(),2))<120
                    ){
           Winer();
 return {true,i};
        }
    }
    return{false,-1};
}
QPair<bool,int> Presenter::calculateBullets(){
    for(int i = 0; i < model_->currentMap.bullets.size();i++){
        if(sqrt(pow(model_->hero.position.x()-model_->currentMap.bullets[i].position.x(),2)
                +pow(model_->hero.position.y()-model_->currentMap.bullets[i].position.y(),2))<60){
            return {true,i};
        }
    }
    return{false,-1};
}
void Presenter::creatingAttac(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
        if(model_->currentMap.enemies[i].name==Enemy::Troll && sqrt(pow(model_->hero.position.x()-model_->currentMap.enemies[i].position.x(),2)
                                                                    +pow(model_->hero.position.y()-model_->currentMap.enemies[i].position.y(),2))<200){

            model_->createFlyingBullet(model_->currentMap.enemies[i].position,"forKillHero",model_->currentMap.enemies[i].trajectory.flagDirection);
        }
    }
}

std::unique_ptr<Model>& Presenter::getModel(){
    return model_;
}

void Presenter::minusLifeOfHero(){
    qDebug()<<"not d";
    if(immortalityForHero->isActive()){
        immortalityForHero->stop();
        view_->changeToHealthy();
    }
    immortalityForHero->start(2000);
     view_->changeToIll();
}
void Presenter::GameOver(){

    timer->stop();//use clear trajectory
    model_->flyingBullets.clear();
    if(immortalityForHero->isActive()){
        immortalityForHero->stop();
         view_->changeToHealthy();
    }
    if(MainTimer->isActive()){
        MainTimer->stop();
        timerForAttack->stop();
    }
    view_->hide();
    menu->ui->level1->setVisible(false);
    menu->ui->level2->setVisible(false);
    menu->ui->label->setVisible(true);
     if(code==Fail){
         menu->ui->label->setText("          Fail");
     }else if(code==Win){
         menu->ui->label->setText("          Win");
     }
     menu->showFullScreen();
}
void Presenter::Winer(){
    code=Win;
    GameOver();
}
QPair<Presenter::EventType, int> Presenter::calculateEvent(){

    for(int j=0; j<model_->flyingBullets.size();++j){
        if(model_->flyingBullets[j].bulletType==Bullet::ForKillEnemy){
            if(calculateKillingEnemy(model_->flyingBullets[j].position).first){
                int num = calculateKillingEnemy(model_->flyingBullets[j].position).second;
                model_->flyingBullets.erase(model_->flyingBullets.begin()+j);
                return {Presenter::Attac,num};
            }
        } else//model_->flyingBullets[j].bulletType==Bullet::ForKillHero
            if(calculateKillingHeroByBullets(model_->flyingBullets[j].position)){
                model_->flyingBullets.erase(model_->flyingBullets.begin()+j);
                return {Presenter::Killing,1};
            }
        }
        if(calculateKillingHero().first){
            return {Presenter::Enemy,calculateKillingHero().second};
        }
        if(calculateCoints().first){
            return {Presenter::Coint,calculateCoints().second};
        }
        if(calculateBullets().first){
            return {Presenter::Bullet,calculateBullets().second};
        }
    return{Presenter::Nothing, -1};
}



