#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include<QPointF>
#include<QString>
#include<vector>
#include<QPair>
class Trajectory
{
public:
    Trajectory(){};
    void setTrajectory(QPair<QPointF, QString> heroAndCode);
    void setTrajectory(std::vector<QPointF>, QString);
    enum Type{
         Not, Up,SetUp, Right, Left, Attack_, Bee, Troll,Snail
    };
    enum End_{Yes, No};
    Type typeOfTrajectory;
    QPointF firstPosition;
    QPointF currentPosition;
    std::vector<QPointF> way;
    QPointF endPos;
    QPair<End_,QPointF> positionByTrajectory();
    //------------------
    int flagDirection=1;
    QPair<End_,QPointF> positionByTime();
    void stopByVerticalRoad();
    void stopByUpHorizontalRoad();
    void stopByDownHorizontalRoad();
    void withoutRoad();
    double V_x=0;
    double V_y=0;
    double a_=0;
};

#endif // TRAJECTORY_H
