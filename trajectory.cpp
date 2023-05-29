#include "trajectory.h"
#include "QDebug"
void Trajectory::setTrajectory(std::vector<QPointF> way_, QString event){
    currentPosition.setX(way_[0].x());
    currentPosition.setY(way_[0].y());
    way=way_;
    //if(event=="Bee"){
    if(event=="Snail"){
        typeOfTrajectory=Trajectory::Snail;
        V_x = 2;
    }
    if(event=="Bee"){
        typeOfTrajectory=Trajectory::Bee;
        V_y = 4;

    }
    if(event=="Troll"){
        typeOfTrajectory=Trajectory::Troll;
        V_x = 3;
    }
}
void Trajectory::setTrajectory(QPair<QPointF, QString> creatureAndCode){
    currentPosition.setX(creatureAndCode.first.x());
    currentPosition.setY(creatureAndCode.first.y());
    if(creatureAndCode.second == "LAttack"){
        typeOfTrajectory = Trajectory::Attack_;
        flagDirection=-1;
        endPos.setX(currentPosition.x()+200*flagDirection);
        V_x=5*flagDirection;
    }else if(creatureAndCode.second == "RAttack"){
        typeOfTrajectory = Trajectory::Attack_;
        flagDirection=1;
        endPos.setX(currentPosition.x()+200*flagDirection);
        V_x=5*flagDirection;
    }else
        if(creatureAndCode.second=="Right"){
            flagDirection=1;

            if(typeOfTrajectory == Trajectory::Up){
                if(abs(V_x)<2)
                    V_x+=1;
            }else{

                typeOfTrajectory = Trajectory::Right;
                V_x=1.5;
                endPos.setX(currentPosition.x()+50);
qDebug()<<"type"<<typeOfTrajectory;
            }
        }
        else
            if(creatureAndCode.second=="Left"){
                flagDirection=-1;
                if(typeOfTrajectory == Trajectory::Up){
                    if(abs(V_x)<2)
                        V_x-=1;
                }else{
                    typeOfTrajectory = Trajectory::Left;
                    V_x=-1.5;
                    endPos.setX(currentPosition.x()-50);

                }
            }else if(creatureAndCode.second == "Up" && abs(V_y)<0.6){
                typeOfTrajectory = Trajectory::Up;
                V_y=4;
                a_=0.05;
            }
};
void Trajectory::withoutRoad(){
    if(V_y==0){
        a_=0.05;}
   typeOfTrajectory=Trajectory::Up;
}

void Trajectory::stopByVerticalRoad(){
   // typeOfTrajectory = Trajectory::Not;
    // a_=0;
    V_x=0;
    //V_y=0;
}

void Trajectory::stopByDownHorizontalRoad(){
  a_=0;

    V_y=0;
    if(typeOfTrajectory==Trajectory::Up){
        V_x=0;

       typeOfTrajectory = Trajectory::Not;
    }
    //typeOfTrajectory = Trajectory::Not;
}
void Trajectory::stopByUpHorizontalRoad(){
    //
    V_y=0;
    if(typeOfTrajectory==Trajectory::Up){
        V_x=0;
        //typeOfTrajectory = Trajectory::Not;
    }
    typeOfTrajectory = Trajectory::Up;
}
QPair<Trajectory::End_,QPointF> Trajectory::positionByTrajectory(){
    if(typeOfTrajectory==Trajectory::Snail || typeOfTrajectory==Trajectory::Troll){
        double x_=  way[0].x()+(currentPosition.x()-way[0].x()+flagDirection*V_x);
        int endX = way.size()-1;
        if(x_ > way[endX].x() || x_ < way[0].x()){
            //x_ -= way[endX].x()-way[0].x();
            flagDirection *=-1;
        }
        currentPosition.setX(x_);
    }
    if(typeOfTrajectory==Trajectory::Bee){
        double y_=  way[0].y()+(currentPosition.y()-way[0].y()+flagDirection*V_y);
        int endX = way.size()-1;
        if(y_ > way[endX].y() || y_ < way[0].y()){
            //x_ -= way[endX].x()-way[0].x();
            flagDirection *=-1;
        }
        currentPosition.setY(y_);
    }return {Yes, currentPosition};//replace
}
QPair<Trajectory::End_,QPointF> Trajectory::positionByTime(){
    currentPosition.rx()+=V_x;
    V_y -= a_*1;
    currentPosition.ry()-=V_y;
   qDebug()<<typeOfTrajectory;
    if(((typeOfTrajectory==Trajectory::Right||typeOfTrajectory==Trajectory::Left
        || typeOfTrajectory==Trajectory::Attack_))&&
            (flagDirection*(currentPosition.x()-endPos.x())>0) ){

        return {No, {currentPosition.x()+V_x,currentPosition.y()-V_y}};
    }
    return {Yes, {currentPosition.x()+V_x,currentPosition.y()-V_y}};

};
