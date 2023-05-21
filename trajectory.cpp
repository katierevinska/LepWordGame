#include "trajectory.h"
#include "QDebug"
void Trajectory::setTrajectory(std::vector<QPointF> way_, QString event){
    currentPosition.setX(way_[0].x());
    currentPosition.setY(way_[0].y());
    way=way_;
    if(event=="Bee"){
        typeOfTrajectory=Trajectory::Bee;
        V_x = 0.2;
    }
    if(event=="Troll"){
        typeOfTrajectory=Trajectory::Troll;
        V_x = 0.5;
    }
}
void Trajectory::setTrajectory(QPair<QPointF, QString> creatureAndCode){

    currentPosition.setX(creatureAndCode.first.x());
    currentPosition.setY(creatureAndCode.first.y());
    if(creatureAndCode.second == "Attack"){
            typeOfTrajectory = Trajectory::Attack_;
            qDebug()<<"flagDirection"<<flagDirection<<V_x;
            endPos.setX(currentPosition.x()+40*flagDirection);
            V_x=1.8*flagDirection;
    }else
        if(creatureAndCode.second=="Right"){
            flagDirection=1;
            if(typeOfTrajectory == Trajectory::Up){
                if(abs(V_x)<2)
                V_x+=1;
            }else{
                typeOfTrajectory = Trajectory::Right;
                V_x=1;
                endPos.setX(currentPosition.x()+20);

}}
            else
                    if(creatureAndCode.second=="Left"){
flagDirection=-1;
                        if(typeOfTrajectory == Trajectory::Up){
                            if(abs(V_x)<2)
                            V_x-=1;
                        }else{
                            typeOfTrajectory = Trajectory::Left;
                            V_x=-1;
                            endPos.setX(currentPosition.x()-20);

            }
    }else if(creatureAndCode.second == "Up" && abs(V_y)<0.25){
            qDebug()<<V_y;
        typeOfTrajectory = Trajectory::Up;
           V_y=4;
           a_=0.2;
    }
};
void Trajectory::stopJump(){
    typeOfTrajectory = Trajectory::Not;
    a_=0;
    V_x=0;
    V_y=0;
}
QPair<Trajectory::End_,QPointF> Trajectory::positionByTrajectory(){
    if(typeOfTrajectory==Trajectory::Bee || typeOfTrajectory==Trajectory::Troll){
qDebug()<<"flag"<<flagDirection<<V_x;
        double x_=  way[0].x()+(currentPosition.x()-way[0].x()+flagDirection*V_x);
        int endX = way.size()-1;
        if(x_ > way[endX].x() || x_ < way[0].x()){
            //x_ -= way[endX].x()-way[0].x();
            flagDirection *=-1;
        }
        currentPosition.setX(x_);


    }return {Yes, currentPosition};//replace
}
QPair<Trajectory::End_,QPointF> Trajectory::positionByTime(){
    currentPosition.rx()+=V_x;
    V_y -= a_*1;
    currentPosition.ry()-=V_y;

    if((typeOfTrajectory==Trajectory::Right||typeOfTrajectory==Trajectory::Left
        || typeOfTrajectory==Trajectory::Attack_)&&
           (flagDirection*(currentPosition.x()-endPos.x())>0) ){
            return {No, currentPosition};
    }
        return {Yes, currentPosition};

};
