#ifndef COINT_H
#define COINT_H
#include <QPointF>

class coint
{
public:
    enum TypeOfGold{
      Coint,Pot
    };
    coint(QPointF position_, TypeOfGold type):position(position_),typeOfGold(type){
        if(type == Coint){
            NumOfGold=10;
        }
        if(type == Pot){
            NumOfGold=510;
        }

    };

    QPointF position;
    TypeOfGold typeOfGold;
    int NumOfGold=10;
};

#endif // COINT_H
