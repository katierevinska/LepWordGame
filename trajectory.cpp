#include "trajectory.h"

void Trajectory::setTrajectory(std::vector<QPointF> way_, QString event){
    currentPosition.setX(way_[0].x());
    currentPosition.setY(way_[0].y());
    way=way_;
    if(event=="Bee"){
        typeOfTrajectory=Trajectory::Bee;
        V_x = 0.2;
    }
}
void Trajectory::setTrajectory(QPair<QPointF, QString> creatureAndCode){

    currentPosition.setX(creatureAndCode.first.x());
    currentPosition.setY(creatureAndCode.first.y());
    if(creatureAndCode.second == "Attack"){
            typeOfTrajectory = Trajectory::Attack_;
            endPos.setX(currentPosition.x()+40);
            V_x=1.8;
    }else
        if(creatureAndCode.second=="Right"){

            if(typeOfTrajectory == Trajectory::Up){
                if(V_x<2)
                V_x+=1;
            }else{
                typeOfTrajectory = Trajectory::Right;
                V_x=1;
                endPos.setX(currentPosition.x()+20);
}
    }else if(creatureAndCode.second == "Up" && V_y<0.7){
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
    if(typeOfTrajectory==Trajectory::Bee){

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

    if((typeOfTrajectory==Trajectory::Right || typeOfTrajectory==Trajectory::Attack_)&&
           (currentPosition.x()>endPos.x()) ){
            return {No, currentPosition};
    }
        return {Yes, currentPosition};

};
