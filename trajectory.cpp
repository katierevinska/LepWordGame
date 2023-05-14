#include "trajectory.h"
#include<QDebug>
void Trajectory::setTrajectory(std::vector<QPointF> way_, QString enemy){
    currentPosition.setX(way_[0].x());
    currentPosition.setY(way_[0].y());
    typeOfTrajectory=Bee;
    way=way_;
    dx = 3;
}
void Trajectory::setTrajectory(QPair<QPointF, QString> heroAndCode){

    firstPosition.setX(heroAndCode.first.x());
    firstPosition.setY(heroAndCode.first.y());
    currentPosition.setX(firstPosition.x());
    currentPosition.setY(firstPosition.y());
    if(heroAndCode.second=="Right"){
        typeOfTrajectory = Right;
        dx=1;
        xAlreadyGone=0;
        endPos.setX(firstPosition.x()+20);
        qDebug()<<":"<<endPos.x();
    }else if(heroAndCode.second == "RightAndUp"){
        typeOfTrajectory = RightAndUp;
        dx=1;
        //xAlreadyGone=0;
        delteX = 30;
        k =20;
    }
    else if(heroAndCode.second == "RightAndDown"){
        typeOfTrajectory = RightAndDown;
        dx=1;
        firstPosition.rx()-=2*dx;
        //xAlreadyGone=0;
        delteX = 3;
        k =15;//calculate
    }
};
QPair<Trajectory::End_,QPointF> Trajectory::positionByTrajectory(){
    if(typeOfTrajectory==Trajectory::Bee){

        double x_=  way[0].x()+(currentPosition.x()-way[0].x()+dx);
        int endX = way.size()-1;
        if(x_ > way[endX].x()){
            x_ -= way[endX].x()-way[0].x();
        }
        currentPosition.setX(x_);

        return {Yes, currentPosition};
    }

    if(typeOfTrajectory==Trajectory::Right){
        currentPosition.rx()+=dx;
        qDebug()<<"*"<<currentPosition.x()<<endPos.x();
        if(currentPosition.x()!=endPos.x()){
            return {Yes, currentPosition};
        }else{
            qDebug()<<"%";
            return {No, currentPosition};
        }
    }if(typeOfTrajectory==Trajectory::RightAndUp){
        currentPosition.setX(currentPosition.x()+dx);
        currentPosition.setY(firstPosition.y()+(currentPosition.x()-firstPosition.x())*(currentPosition.x()-firstPosition.x()-2*delteX)/k);
        qDebug()<<"+"<<currentPosition.x()<<currentPosition.y();
        return {Yes, {currentPosition.x(),currentPosition.y()}};
    }
//else if RightAndDown
    currentPosition.setX(currentPosition.x()+dx);
    currentPosition.setY(firstPosition.y()+(currentPosition.x()-(firstPosition.x()-delteX))*(currentPosition.x()-(firstPosition.x()+delteX))/k);

    return {Yes, {currentPosition.x(),currentPosition.y()}};
};
