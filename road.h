#ifndef ROAD_H
#define ROAD_H
#include <QPolygonF>

class Road
{
public:
    QPolygonF polygon;
    enum TypeRoad{
        Ground, Block
    };
    TypeRoad typeRoad;
    Road(QPointF, TypeRoad);
};

#endif // ROAD_H
