#include "presenter.h"
#include "view.h"
#include<QObject>
#include<QDebug>
Presenter::Presenter():
view_(std::make_unique<View>(this)),
model_(std::make_unique<Model>()) {
 view_->show();
 timer = new QTimer(this);

 connect( timer, &QTimer::timeout, this, &Presenter::moveHero);
}
std::unique_ptr<Model>& Presenter::getModel(){
    return model_;
}
void Presenter::GameOver(){
    qDebug()<<"!";
    view_->mess->setText("end(");
    killTimer(timerId);
};
void Presenter::moveHero(){
    model_->hero.position.rx()+=20;
    if(model_->hero.position.rx()==trajectory[1].rx()){
        timer->stop();
    }
}
void Presenter::setTrajectory(QString str){
    if(str == "Right"){
        trajectory[0] =model_->hero.position;
        trajectory[1] ={model_->hero.position.x()+40, model_->hero.position.y()};
    }
}
void Presenter::moveEvents(QString str){
    timer->start(500);
        setTrajectory(str);
}
void Presenter::startGame(int numLeven){
    setLevel(numLeven);
    timerId = startTimer(500);
    view_->mess->setText("try");
}
void Presenter::timerEvent(QTimerEvent *event){
    model_->changeEnemiesPosition();
    changeData(calculateEvent());
    view_->update();
}
QPair<Presenter::EventType, int> Presenter::calculateEvent(){
    for(int i = 0; i < model_->currentMap.enemies.size();i++){
        if(model_->hero.position==model_->currentMap.enemies[i].position){
            return {Presenter::Enemy,i};
        }
    }
    return{Presenter::Nothing, -1};
}
void Presenter::setLevel(int level){
    if(level == 1){
        model_->SetModelByLevel(level);
    }
};
void Presenter::changeData(QPair<Presenter::EventType, int> eventPair){

    if(eventPair.first==Presenter::Enemy){
model_->hero.NumberOfLives--;
    }
    if(model_->hero.NumberOfLives==0){
        GameOver();
    }
    //model_->enemies.erase(model_->enemies.cbegin()+eventPair.second);
    //+отнять жизнь\увеличить счёт\\вызвать !/ update()
    //!todododo
}
