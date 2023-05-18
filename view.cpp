#include "view.h"
#include"abstract_presenter.h"
#include "model.h"
#include<vector>
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
}

View::~View(){}

void View::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.save();
    QPointF point((double)this->width(),(double)this->height());
    std::vector<QPointF> pol{{0,0},{point.x(),0},point, {0,point.y()}};
    painter.setPen({Qt::black, 1});
    painter.setBrush(QColor (255, 255, 255, 255));
    //painter.drawPolygon({{pol}});
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
        painter->drawEllipse({bullet.position},3,3);
    for(auto bullet_: presenter_->getModel().get()->flyingBullets){
        painter->drawEllipse(bullet_.position,3,3);
    }
}
void View::painterCoints(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);
    for(auto coint: presenter_->getModel().get()->currentMap.coints)
        painter->drawEllipse({coint.position},3,3);
}
void View::painterHero(QPainter* painter){
    QBrush brush(Qt::green);
    painter->setBrush(brush);
    painter->drawEllipse({presenter_->getModel().get()->hero.position},5,5);
}
void View::painterMapWay(QPainter* painter){
    QBrush brush(Qt::yellow);
    painter->setBrush(brush);
for(auto pol: presenter_->getModel().get()->currentMap.way){
    painter->drawPolyline(pol);
  //  painter->drawPolyline(presenter_->getModel().get()->currentMap.way[0]);
}
}
void View::painterEnemies(QPainter* painter){
    QBrush brush(Qt::red);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    for(auto enemy: presenter_->getModel().get()->currentMap.enemies)
        painter->drawEllipse({enemy.position},5,5);
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

