#include "firstmenu.h"
#include "ui_firstmenu.h"

FirstMenu::FirstMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstMenu)
{

    ui->setupUi(this);//rgb(0, 170, 0)
    QPixmap bkgnd(":/image/startPict.png");
        bkgnd = bkgnd.scaled(this->size());
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
        ui->label->setStyleSheet(        "background-color: rgb(255, 85, 0,100);"
                                               "font: 700 20pt;");
    ui->start->setStyleSheet(        "background-color: rgb(0,170,0,100);"
                                           "font: 700 20pt;");
    ui->level1->setStyleSheet(" background-color: rgb(0, 170, 255,100);""font: 700 20pt;");
    ui->level2->setStyleSheet(" background-color: rgb(0, 170, 255,100);""font: 700 20pt;");

}
void FirstMenu::keyPressEvent(QKeyEvent* event){

 if(event->key()==Qt::Key_Escape){
close();
        }
}


FirstMenu::~FirstMenu()
{
    delete ui;
}
