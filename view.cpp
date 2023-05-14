#include "view.h"
#include"abstract_presenter.h"
#include "model.h"
#include <QPainter>

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
    painterHero(&painter);
    painterMapWay(&painter);
    painterEnemies(&painter);
    painterCoints(&painter);
    painter.restore();
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
    //for(int i = 0; i < presenter_->getModel().get()->currentMap.way.size()-1; i++){
    painter->drawLine((presenter_->getModel().get()->currentMap.way)[0], presenter_->getModel().get()->currentMap.way[1]);
    //}
}
void View::painterEnemies(QPainter* painter){
    QBrush brush(Qt::red);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    for(auto enemy: presenter_->getModel().get()->currentMap.enemies)
        painter->drawEllipse({enemy.position},5,5);
}
void View::keyPressEvent(QKeyEvent* event){
/*if(event->key()==Qt::Key_W){
   presenter_->moveEvents("Up");
} else */
    if(event->key()==Qt::Key_D){
        presenter_->moveEvents("Right");
    } else if(event->key()==Qt::Key_W){
        presenter_->/*getModel().get()->*/moveEvents("RightAndUp");
    } /*else if(event->key()==Qt::Key_Enter){
presenter_->moveEvents("Attack");
} else if(event->key()==Qt::Key_Enter+Qt::Key_D){
    presenter_->moveEvents("RightAndAttack");
} else if(event->key()==Qt::Key_Enter+Qt::Key_W){
   presenter_->moveEvents("UpAndAttack");
} else if(event->key()==Qt::Key_Enter+Qt::Key_W+Qt::Key_D){
  presenter_->moveEvents("RightAndUpAndAttack");
}*/
}

