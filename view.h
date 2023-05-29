#ifndef VIEW_H
#define VIEW_H
#include "abstract_presenter.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include<QPixmap>

class View: public QMainWindow
{
    Q_OBJECT
public:
    View(abstract_presenter* presenter);
    ~View();

    void paintEvent(QPaintEvent* event) override;
    void painterHero(QPainter* painter);
    void painterMapWay(QPainter* painter);
    void painterEnemies(QPainter* painter);
    void painterCoints(QPainter* painter);
    void painterBullets(QPainter* painter);
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void changeToHealthy();
    void changeToIll();
 double p_x=0;
private:
QPixmap mapGr;
QPixmap mapBlock;
QPixmap mapHero;
QPixmap mapSky;
QPixmap mapCoint;
QPixmap mapPot;
QPixmap addingBullet;
QPixmap mapBullet;
QPixmap mapEnemu3;
QPixmap mapEnemu2;
QPixmap mapEnemu1;
    abstract_presenter* presenter_;
    QGridLayout* layout_;
    QWidget* central_widget_;
public://!
    QPushButton* level1;
    QLabel* mess;

};

#endif // VIEW_H
