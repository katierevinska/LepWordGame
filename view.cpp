#include "view.h"
#include "abstract_presenter.h"
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
    painter.restore();
}
void View::painterHero(QPainter* painter){
    QBrush brush(Qt::yellow);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    painter->drawEllipse({presenter_->getModel().get()->hero.position},5,5);
}
void View::painterMapWay(QPainter* painter){
    QBrush brush(Qt::yellow);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    painter->drawLine((presenter_->getModel().get()->currentMap.way)[0], presenter_->getModel().get()->currentMap.way[1]);
}
void View::painterEnemies(QPainter* painter){
    QBrush brush(Qt::red);
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    painter->setBrush(brush);
    painter->drawEllipse({presenter_->getModel().get()->currentMap.enemies[0].position},5,5);
}
void View::keyPressEvent(QKeyEvent* event){
if(event->key()==Qt::Key_D){
    presenter_->moveEvents("Right");
}
}
