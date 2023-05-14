#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include<QPoint>
#include<QString>
#include<vector>
#include<QPair>
class Trajectory
{
public:
    Trajectory(){};
    void setTrajectory(QPair<QPointF, QString> heroAndCode);
    void setTrajectory(std::vector<QPointF>, QString);
    double xAlreadyGone;
    double dx;
    enum Type{
        Up, Right, RightAndUp,RightAndDown, Attack_, Bee
    };
    Type typeOfTrajectory;
    QPointF firstPosition;
    QPointF currentPosition;
    std::vector<QPointF> way;
    enum End_{Yes, No};
    QPointF endPos;
    double delteX;
    double k;
    QPair<End_,QPointF> positionByTrajectory();
};

#endif // TRAJECTORY_H
