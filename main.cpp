#include "presenter.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Presenter presenter;
   // QIcon ico (":/image/im.bmp");
    QIcon ico (":/image/unnamed.png");
    a.setWindowIcon(ico);
    return a.exec();
}
