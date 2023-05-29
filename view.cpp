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
             mess(new QLabel("",central_widget_))
{
   // layout_->addWidget(level1, 2, 1, 1, 2);
    layout_->addWidget(mess, 1, 0, 1, 2);
    central_widget_->setLayout(layout_);
    setCentralWidget(central_widget_);
    //connect(level1, &QPushButton::clicked, this, [&] {presenter_->startGame(1);});
   mapSky.load( ":/image/sky.png");
   QPointF point((double)this->width(),(double)this->height());
  mapSky= mapSky.scaled(point.x(),point.y());
   mapHero.load(":/image/unnamed.png");/**/
 mapHero=  mapHero.scaled(65,100);
   mapGr.load(":/image/ground.png");
  mapGr= mapGr.scaled(250,250);
  mapBlock.load(":/image/block.png");
  mapBlock=mapBlock.scaled(50,50);
  mapCoint.load(":/image/cointss.png");
  mapCoint=mapCoint.scaled(30,30);
  mapBullet.load(":/image/bullet.png");
  mapBullet=mapBullet.scaled(15,15);
  addingBullet.load(":/image/addingBullet.png");
  addingBullet=addingBullet.scaled(30,40);
  mapEnemu2.load(":/image/enemy2.png");
  mapEnemu2=mapEnemu2.scaled(90,70);
  mapEnemu1.load(":/image/enemy1.png");
  mapEnemu1=mapEnemu1.scaled(50,50);
  mapEnemu3.load(":/image/bee.png");
  mapEnemu3=mapEnemu3.scaled(80,70);
  mapPot.load(":/image/goold.png");
  mapPot=mapPot.scaled(120,120);
}
void View::changeToHealthy(){mapHero.load(":/image/unnamed.png");
                            mapHero=  mapHero.scaled(65,100);}
void View::changeToIll(){mapHero.load(":/image/unnamedill.png");
                        mapHero=  mapHero.scaled(65,100);}
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

    painter.translate(p_x,0);

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
       painter->drawPixmap( {bullet.position},addingBullet);
    for(auto bullet_: presenter_->getModel().get()->flyingBullets){
        //painter->drawEllipse(bullet_.position,3,3);
        painter->drawPixmap( {bullet_.position},mapBullet);
    }
}
void View::painterCoints(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);

    for(auto coint: presenter_->getModel().get()->currentMap.coints){
        if(coint.typeOfGold==coint::Coint){
        painter->drawPixmap({coint.position},mapCoint);
        }else if(coint.typeOfGold==coint::Pot){
            painter->drawPixmap({coint.position},mapPot);
        }
      //painter->drawEllipse({coint.position},5,5);
}
}
void View::painterHero(QPainter* painter){
    QBrush brush(Qt::green);
    painter->setBrush(brush);
    QPointF posHero(presenter_->getModel().get()->hero.position.x()-30,
                     presenter_->getModel().get()->hero.position.y()-84);
    QString infB="bullets:"+QString::number(presenter_->getModel().get()->hero.bullets);
    QString infL="lifes:"+QString::number(presenter_->getModel().get()->hero.NumberOfLives);

//    painter->drawText((int)posHero.x()+4,(int)posHero.y()-23,infB);
//    painter->drawText((int)posHero.x()+4,(int)posHero.y()-33,infL);
    if(presenter_->getModel().get()->hero.trajectory.flagDirection==-1)
    {
    QMatrix rm;
        rm.scale(-1,1);
      QPixmap mapHero(mapHero.transformed(rm)) ;
       painter->drawPixmap({posHero},mapHero);

    }else{
    painter->drawPixmap({posHero},mapHero);

}}
void View::painterMapWay(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);
//    for(int i =0; i <presenter_->getModel().get()->currentMap.way.size();++i ){
//        qDebug()<<presenter_->getModel().get()->currentMap.way[i].polygon[0]<<
//                    presenter_->getModel().get()->currentMap.way[i].typeRoad;
//    }
for(auto pol: presenter_->getModel().get()->currentMap.way){
    if(pol.typeRoad==Road::Ground){
   painter->drawPixmap(pol.polygon[0],mapGr);
    }
    else if(pol.typeRoad==Road::Block){
   painter->drawPixmap(pol.polygon[0],mapBlock);
    }
   //painter->drawPolyline(pol);
}
}
void View::painterEnemies(QPainter* painter){
    QBrush brush(Qt::red);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    for(auto enemy: presenter_->getModel().get()->currentMap.enemies){
       if(enemy.name==Enemy::Troll){
           if(enemy.trajectory.flagDirection==1)
           {
           QMatrix rm;
               rm.scale(-1,1);
             QPixmap mapEnemu2(mapEnemu2.transformed(rm)) ;
              painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()-10}},mapEnemu2);

           }else{
        painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()-10}},mapEnemu2);
        painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()-10}},mapEnemu2);

    }}else if(enemy.name==Enemy::Snail){
           if(enemy.trajectory.flagDirection==-1)
           {
           QMatrix rm;
               rm.scale(-1,1);
             QPixmap mapEnemu1(mapEnemu1.transformed(rm)) ;
              painter->drawPixmap({{(int)enemy.position.x(),(int)enemy.position.y()}},mapEnemu1);

           }else{
     painter->drawPixmap({enemy.position},mapEnemu1);

}}
       else if(enemy.name==Enemy::Bee){
            painter->drawPixmap({enemy.position},mapEnemu3);

       }
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
 if(event->key()==Qt::Key_Escape){
close();
        }
}

