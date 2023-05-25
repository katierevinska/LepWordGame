#include "road.h"
#include<QDebug>
Road::Road(QPointF point, Road::TypeRoad type)
{
    if(type == Ground){
        polygon={{point,{point.x()+250,point.y()},{point.x()+250,point.y()+250},{point.x(),point.y()+250}}};
 typeRoad=Ground;
    }
    if(type == Block){
        polygon={{point,{point.x()+45,point.y()},{point.x()+45,point.y()+45},{point.x(),point.y()+45}}};
  typeRoad=Block;
    }
}
