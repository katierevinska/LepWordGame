#include "view.h"
#include"abstract_presenter.h"
#include "model.h"
#include<vector>
#include<QMatrix>
View::View(abstract_presenter* presenter)
        :    QMainWindow(nullptr),
             presenter_(presenter),
             layout_(new QGridLayout()),
             central_widget_(new QWidget(this)),
             level1(new QPushButton("Level 1", central_widget_)),
             mess(new QLabel("",central_widget_))
{
    layout_->addWidget(level1, 2, 1, 1, 2);
    layout_->addWidget(mess, 1, 0, 1, 2);
    central_widget_->setLayout(layout_);
    setCentralWidget(central_widget_);
    connect(level1, &QPushButton::clicked, this, [&] {presenter_->startGame(1);});
   mapSky.load( ":/image/sky.png");
   QPointF point((double)this->width(),(double)this->height());
  mapSky= mapSky.scaled(point.x(),point.y());
   mapHero.load(":/image/unnamed.png");
 mapHero=  mapHero.scaled(65,100);
   mapGr.load(":/image/ground.png");
  mapGr= mapGr.scaled(250,250);
  mapBlock.load(":/image/block.png");
  mapBlock=mapBlock.scaled(50,50);
  mapCoint.load(":/image/cointss.png");
  mapCoint=mapCoint.scaled(30,30);
  mapBullet.load(":/image/bullet.png");
  mapBullet=mapBullet.scaled(15,15);
  mapEnemu2.load(":/image/enemy2.png");
  mapEnemu2=mapEnemu2.scaled(50,100);
  mapEnemu1.load(":/image/enemy1.png");
  mapEnemu1=mapEnemu1.scaled(50,50);
}

View::~View(){}
void View::resizeEvent(QResizeEvent* event){
    QPointF point((double)this->width(),(double)this->height());
   mapSky= mapSky.scaled(point.x(),point.y());
}
void View::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.save();
    QPointF point((double)this->width(),(double)this->height());

    painter.drawPixmap({{0,0}},mapSky);
    //painter.translate(p_x,0);
    //painter.translate(p_x,0);
    p_x-=0.0001;
    painterHero(&painter);
    painterMapWay(&painter);
    painterEnemies(&painter);
    painterCoints(&painter);
    painterBullets(&painter);
    painter.restore();
}
void View::painterBullets(QPainter* painter){
    QBrush brush(Qt::black);
    painter->setBrush(brush);
    for(auto bullet: presenter_->getModel().get()->currentMap.bullets)
        //painter->drawEllipse({bullet.position},4,4);
       painter->drawPixmap( {bullet.position},mapBullet);
    for(auto bullet_: presenter_->getModel().get()->flyingBullets){
        //painter->drawEllipse(bullet_.position,3,3);
        painter->drawPixmap( {bullet_.position},mapBullet);
    }
}
void View::painterCoints(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);

    for(auto coint: presenter_->getModel().get()->currentMap.coints){
        painter->drawPixmap({coint.position},mapCoint);
      //painter->drawEllipse({coint.position},5,5);
}
}
void View::painterHero(QPainter* painter){
    QBrush brush(Qt::green);
    painter->setBrush(brush);
    QPointF posHero(presenter_->getModel().get()->hero.position.x()-30,
                     presenter_->getModel().get()->hero.position.y()-84);
    if(presenter_->getModel().get()->hero.trajectory.flagDirection==-1)
    {
    QMatrix rm;
        rm.scale(-1,1);
      QPixmap mapHero(mapHero.transformed(rm)) ;
       painter->drawPixmap({posHero},mapHero);
    }else{
    painter->drawPixmap({posHero},mapHero);
    //painter->drawEllipse({presenter_->getModel().get()->hero.position},8,8);
}}
void View::painterMapWay(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);
    for(int i =0; i <presenter_->getModel().get()->currentMap.way.size();++i ){
        qDebug()<<presenter_->getModel().get()->currentMap.way[i].polygon[0]<<
                    presenter_->getModel().get()->currentMap.way[i].typeRoad;
    }
for(auto pol: presenter_->getModel().get()->currentMap.way){
    if(pol.typeRoad==Road::Ground){
   painter->drawPixmap(pol.polygon[0],mapGr);
    qDebug()<<"graund"<<pol.polygon[0];}
    else if(pol.typeRoad==Road::Block){
   painter->drawPixmap(pol.polygon[0],mapBlock);
     qDebug()<<"bl"<<pol.polygon[0];}
   //painter->drawPolyline(pol);
}
}
void View::painterEnemies(QPainter* painter){
    QBrush brush(Qt::red);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    for(auto enemy: presenter_->getModel().get()->currentMap.enemies){
       if(enemy.name==Enemy::Troll){
           if(enemy.trajectory.flagDirection==-1)
           {
           QMatrix rm;
               rm.scale(-1,1);
             QPixmap mapEnemu2(mapEnemu2.transformed(rm)) ;
              painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()-40}},mapEnemu2);
           }else{
        painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()-40}},mapEnemu2);
    }}if(enemy.name==Enemy::Bee)
     painter->drawPixmap({enemy.position},mapEnemu1);
        //painter->drawEllipse({enemy.position},10,10);
}
}
void View::keyPressEvent(QKeyEvent* event){
if(event->key()==Qt::Key_W){
   presenter_->moveEvents("Up");
}
    if(event->key()==Qt::Key_D){
        presenter_->moveEvents("Right");
    }

        if(event->key()==Qt::Key_A){
            presenter_->moveEvents("Left");
        }
    if(event->key()==Qt::Key_E){
 presenter_->moveEvents("Attack");
        }
}

