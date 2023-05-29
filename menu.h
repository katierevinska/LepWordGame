//#ifndef MENU_H
//#define MENU_H
//#include<QRadioButton>
//#include<QMainWindow>
//#include<QPushButton>
//#include<QBoxLayout>
//#include<QRadioButton>


//QT_BEGIN_NAMESPACE
//namespace Ui { class Menu; }
//QT_END_NAMESPACE

//class Menu: public QMainWindow
//{
//    Q_OBJECT
//public:
//    Menu():QMainWindow(nullptr),
//        ui(new Ui::Menu),
//        layout_(new QVBoxLayout()),
//        mainLayout_ (new QHBoxLayout()),
//        central_widget_(new QWidget(this)),
//    level1(new QRadioButton("Level 1", central_widget_)),
//    level2(new QRadioButton("Level 2", central_widget_)),
//      start(new QPushButton("Start", central_widget_))
//    {
//        layout_->addWidget(level1);
//        layout_->addWidget(level2);
//        mainLayout_->addLayout(layout_);
//        mainLayout_->addWidget(start);
//         central_widget_->setLayout(mainLayout_);
//         setCentralWidget(central_widget_);

//    }
//    ~Menu(){};
////    QRadioButton* level1;
////    QRadioButton* level2;
//    QVBoxLayout* layout_;
//    QHBoxLayout* mainLayout_;
//    QWidget* central_widget_;
//    QRadioButton* level1;
//    QRadioButton* level2;
//    QPushButton* start;
//private:
//    Ui::Menu *ui;
//};

//#endif // MENU_H
