#include "presenter.h"
#include "view.h"
#include<QObject>
//#include<QDebug>

//как обработать то что нельзя идти по воздуху? наверное считать траекторию учитывая положение от земли.

Presenter::Presenter():
        view_(std::make_unique<View>(this)),
        model_(std::make_unique<Model>()) {
    view_->show();
    timer = new QTimer(this);
    connect( timer, &QTimer::timeout, this, &Presenter::moveTimeHero);
}
void Presenter::moveEvents(QString str){
    if(str=="Bullet"){
        if(model_->hero.bullets>0){
        model_->createFlyingBullet(model_->hero.position);
        model_->hero.bullets--;
        }
    }else{
    if(timer->isActive()){

        timer->stop();
    }
    timer->start(50);
    if(str=="Right" && calcRoad().first == Presenter::Nothing){
        str="RightAndDown";
    }
    if((str=="RightAndUp")&&model_->currentMap.way[0].y()-model_->hero.position.y()>30){//change
        return;
    }
        model_->hero.trajectory.setTrajectory({model_->hero.position,str});
    }

}
void Presenter::moveTimeHero(){

    QPair<Trajectory::End_,QPointF> pair = model_->hero.trajectory.positionByTrajectory();
    if(pair.first==Trajectory::Yes){
        model_->hero.position = pair.second;
        if((model_->hero.trajectory.typeOfTrajectory == Trajectory::RightAndUp||model_->hero.trajectory.typeOfTrajectory == Trajectory::RightAndDown) && calcRoad().first==Presenter::Road) {timer->stop();}
    } else{
        model_->hero.position = {pair.second};
        timer->stop();//clearTraj
    }
}
void Presenter::startGame(int numLeven){
    GameOver();

    setLevel(numLeven);
    code = Go;
    timerId = startTimer(100);
    view_->mess->setText("try");

}
void Presenter::setLevel(int level){
    if(level == 1){

        model_->SetModelByLevel(level);

    }
};
void Presenter::timerEvent(QTimerEvent *event){

    model_->changeEnemiesPosition();//not main!!!

    model_->changeFlyingBulletsPosition();
    changeData(calculateEvent());
    //view_->update();
}
QPair<Presenter::EventType, int> Presenter::calcRoad(){
    int i=0;
    double X_=model_->currentMap.way[i].x();
    double Y_=model_->currentMap.way[i].y();
    while (!(model_->hero.position.x()==X_)) {
        if(X_!=model_->currentMap.way[i+1].x()){
            X_+=1;
        }else{
            i++;
            if(i+1==model_->currentMap.way.size()){//тут тоже будет дорога, не пустота потом
                GameOver();
            }
        }
    }
    if(abs(model_->hero.position.y()-Y_)<2){
        return{Presenter::Road, i};
    }
    else{
        return{Presenter::Nothing, -1};
    }
}
QPair<Presenter::EventType, int> Presenter::calculateEvent(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
        for(int j=0; j<model_->flyingBullets.size();++j){
            if(pow(model_->currentMap.enemies[i].position.x()-model_->flyingBullets[j].position.x(),2)+pow(model_->currentMap.enemies[i].position.y()-model_->flyingBullets[j].position.y(),2)<25){
                model_->flyingBullets.erase(model_->flyingBullets.begin()+j);
                return {Presenter::Attac,i};
            }
        }
        if(pow(model_->hero.position.x()-model_->currentMap.enemies[i].position.x(),2)+pow(model_->hero.position.y()-model_->currentMap.enemies[i].position.y(),2)<100){
            return {Presenter::Enemy,i};
        }
    }
    for(int i = 0; i < model_->currentMap.coints.size();i++){
        if(pow(model_->hero.position.x()-model_->currentMap.coints[i].position.x(),2)+pow(model_->hero.position.y()-model_->currentMap.coints[i].position.y(),2)<100){
            return {Presenter::Coint,i};
        }
    }
    for(int i = 0; i < model_->currentMap.bullets.size();i++){
        if(pow(model_->hero.position.x()-model_->currentMap.bullets[i].position.x(),2)+pow(model_->hero.position.y()-model_->currentMap.bullets[i].position.y(),2)<100){
            return {Presenter::Bullet,i};
        }
    }
    return{Presenter::Nothing, -1};
}
void Presenter::GameOver(){
    view_->mess->setText("end(");
    timer->stop();//use clear trajectory
    model_->flyingBullets.clear();
    if(code==Go){
        killTimer(timerId);
    }
};
void Presenter::changeData(QPair<Presenter::EventType, int> eventPair){
    view_->update();//delete!
    if(eventPair.first==Presenter::Enemy){
        model_->hero.NumberOfLives--;
        if(model_->hero.NumberOfLives==0){
            GameOver();
        }
    }
    if(eventPair.first==Presenter::Attac){
        model_->currentMap.enemies[eventPair.second].NumOfAttackForDeath--;
        if(model_->currentMap.enemies[eventPair.second].NumOfAttackForDeath==0){
            model_->currentMap.enemies.erase(model_->currentMap.enemies.begin()+eventPair.second);
        }
    }
    if(eventPair.first==Presenter::Coint){
        model_->gold+=model_->currentMap.coints[eventPair.second].NumOfGold;
        model_->currentMap.coints.erase(model_->currentMap.coints.begin()+eventPair.second);
    }
    if(eventPair.first==Presenter::Bullet){
      model_->hero.bullets+=model_->currentMap.bullets[eventPair.second].num;
 qDebug()<<model_->hero.bullets;
        model_->currentMap.bullets.erase(model_->currentMap.bullets.begin()+eventPair.second);
    }
        //else if Presenter::Way->>timer.stop(),view_->update(),trajectory.clear
    else if(eventPair.first==Presenter::Nothing){

        //view_->update()
        //nobody stoped movetimer!!!
    }
    //model_->enemies.erase(model_->enemies.cbegin()+eventPair.second);
    //+отнять жизнь\увеличить счёт
}

std::unique_ptr<Model>& Presenter::getModel(){
    return model_;
}


