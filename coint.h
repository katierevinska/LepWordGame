#ifndef COINT_H
#define COINT_H
#include <QPoint>

class coint
{
public:
    coint(QPointF position_):position(position_){};
    QPointF position;
    int NumOfGold=10;
};

#endif // COINT_H
