#include "presenter.h"
#include "view.h"
#include<QObject>
#include <cmath>

Presenter::Presenter():
    view_(std::make_unique<View>(this)),
    model_(std::make_unique<Model>()) {
    view_->show();
    timer = new QTimer(this);
    timerForAttack = new QTimer(this);
    immortalityForHero = new QTimer(this);
    connect( timer, &QTimer::timeout, this, &Presenter::moveTimeHero);
    connect( timerForAttack, &QTimer::timeout, this, &Presenter::creatingAttac);
    connect( immortalityForHero, &QTimer::timeout, this, [this]{immortalityForHero->stop();
    qDebug()<<"stop";});
}
void Presenter::moveEvents(QString str){
    if(str=="Attack"){
        if(model_->hero.bullets>0){
            model_->createFlyingBullet(model_->hero.position,"forKillEnemy");
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

    QPair<Trajectory::End_,QPointF> pair = model_->hero.trajectory.positionByTime();
     model_->hero.position = pair.second;
     if(pair.first==Trajectory::No){
         model_->hero.trajectory.stopJump();
        timer->stop();
    }
}
void Presenter::startGame(int numLeven){
    GameOver();
    setLevel(numLeven);
    code = Go;
    timerId = startTimer(10);
    view_->mess->setText("try");
timerForAttack->start(200);
}
void Presenter::setLevel(int level){
    if(level == 1){

        model_->SetModelByLevel(level);

    }
};
void Presenter::timerEvent(QTimerEvent *event){
    model_->changeEnemiesPosition();
    model_->changeFlyingBulletsPosition();
    changeData(calculateEvent());
view_->update();
}
QPair<Presenter::EventType, int> Presenter::calcRoad(){
    QPolygonF hero({{model_->hero.position.x()-2,model_->hero.position.y()},
                    {model_->hero.position.x()+2,model_->hero.position.y()},
                    {model_->hero.position.x()+2,model_->hero.position.y()+3},
                    {model_->hero.position.x()-2,model_->hero.position.y()+3}});
    if(model_->currentMap.way[0].intersects(hero)){
    //if(model_->currentMap.way[0].contains(model_->hero.position)){
        model_->hero.position={model_->hero.position.x(), model_->hero.position.y()-5};
        return{Presenter::Road, 0};
    }
    else
    {
        return{Presenter::Nothing, -1};
    }
}
QPair<bool,int> Presenter::calculateKillingEnemy(QPointF position){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
       if(pow(model_->currentMap.enemies[i].position.x()-position.x(),2)+
               pow(model_->currentMap.enemies[i].position.y()-position.y(),2)<45){
           return {true,i};
       }
    }
    return {false,-1};
}
bool Presenter::calculateKillingHeroByBullets(QPointF position){
    if(pow(position.x()- model_->hero.position.x(),2)+
            pow(position.y()-model_->hero.position.y(),2)<45){
        return true;
}
    return false;
}
QPair<bool,int> Presenter::calculateKillingHero(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
   if(!(immortalityForHero->isActive()) && sqrt(pow(model_->hero.position.x()-model_->currentMap.enemies[i].position.x(),2)
           +pow(model_->hero.position.y()-model_->currentMap.enemies[i].position.y(),2))<10){
       return {true,i};
   }
    }
   return {false,-1};
}
QPair<bool,int> Presenter::calculateCoints(){
    for(int i = 0; i < model_->currentMap.coints.size();i++){
        if(pow(model_->hero.position.x()-model_->currentMap.coints[i].position.x(),2)
                +pow(model_->hero.position.y()-model_->currentMap.coints[i].position.y(),2)<100){
            return {true,i};
        }
    }
    return{false,-1};
}
QPair<bool,int> Presenter::calculateBullets(){
for(int i = 0; i < model_->currentMap.bullets.size();i++){
    if(pow(model_->hero.position.x()-model_->currentMap.bullets[i].position.x(),2)
            +pow(model_->hero.position.y()-model_->currentMap.bullets[i].position.y(),2)<100){
        return {true,i};
    }
}
return{false,-1};
}
void Presenter::creatingAttac(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
   if(model_->currentMap.enemies[i].name==Enemy::Troll && sqrt(pow(model_->hero.position.x()-model_->currentMap.enemies[i].position.x(),2)
           +pow(model_->hero.position.y()-model_->currentMap.enemies[i].position.y(),2))<60){
       qDebug()<<"forKilling";
       model_->createFlyingBullet(model_->currentMap.enemies[i].position,"forKillHero");
   }
    }
}
QPair<Presenter::EventType, int> Presenter::calculateEvent(){

     for(int j=0; j<model_->flyingBullets.size();++j){
         if(model_->flyingBullets[j].bulletType==Bullet::ForKillEnemy){
         if(calculateKillingEnemy(model_->flyingBullets[j].position).first){
             model_->flyingBullets.erase(model_->flyingBullets.begin()+j);
             return {Presenter::Attac,calculateKillingEnemy(model_->flyingBullets[j].position).second};
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
void Presenter::GameOver(){
    view_->mess->setText("end(");
    timer->stop();//use clear trajectory
    model_->flyingBullets.clear();
    if(code==Go){
        killTimer(timerId);
        timerForAttack->stop();
    }
};
void Presenter::minusLifeOfHero(){
    qDebug()<<"not d";
    if(immortalityForHero->isActive()){
       immortalityForHero->stop();
    }
    immortalityForHero->start(2000);
};
void Presenter::changeData(QPair<Presenter::EventType, int> eventPair){
    if(eventPair.first==Presenter::Killing){
        model_->hero.NumberOfLives--;
        if(model_->hero.NumberOfLives==0){
            GameOver();
        }
    }
    if(eventPair.first==Presenter::Enemy){
        model_->hero.NumberOfLives--;
        if(model_->hero.NumberOfLives==0){
            GameOver();
        }else{
            minusLifeOfHero();
            qDebug()<<"-";
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
        model_->currentMap.bullets.erase(model_->currentMap.bullets.begin()+eventPair.second);
    }
    if(model_->hero.trajectory.typeOfTrajectory ==Trajectory::Up && calcRoad().first
            ==Presenter::Road){
        model_->hero.trajectory.stopJump();
        timer->stop();
    }
}

std::unique_ptr<Model>& Presenter::getModel(){
    return model_;
}


