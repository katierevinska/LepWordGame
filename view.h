#ifndef VIEW_H
#define VIEW_H
#include "abstract_presenter.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QKeyEvent>
#include <QLabel>
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
    void keyPressEvent(QKeyEvent* event) override;
private:
    abstract_presenter* presenter_;
    QGridLayout* layout_;
    QWidget* central_widget_;
public://!
    QPushButton* level1;
    QLabel* mess;

};

#endif // VIEW_H
