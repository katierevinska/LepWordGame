#ifndef FIRSTMENU_H
#define FIRSTMENU_H

#include <QMainWindow>
#include<QKeyEvent>
namespace Ui {
class FirstMenu;
}

class FirstMenu : public QMainWindow
{
    Q_OBJECT
public:
    FirstMenu(QWidget *parent);

    ~FirstMenu();
    void keyPressEvent(QKeyEvent* event) override;
    Ui::FirstMenu *ui;
};


#endif // FIRSTMENU_H
