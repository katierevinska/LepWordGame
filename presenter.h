#ifndef PRESENTER_H
#define PRESENTER_H
#include"firstmenu.h"
#include "model.h"
#include "view.h"
#include "abstract_presenter.h"
#include "trajectory.h"
#include<memory>
#include<QTimer>
#include<QElapsedTimer>
#include<QPair>

class Presenter : public abstract_presenter
{
public:
    Presenter();
    enum EventType{
        Coint, Enemy, Nothing,DownHorizontalRoad, UpHorizontalRoad,
        VerticalRoad ,Bullet ,Attac, Killing, Failing
    };
    enum GameCode {
        Fail, Win, Go
    };
    GameCode code;
    void timerEvent();
    void moveEvents(QString str) override;
    void startGame(int) override;
    void GameOver();
    void Winer();
    void setLevel(int);
    void creatingAttac();
    void minusLifeOfHero();
QTimer * immortalityForHero;
    QPair<EventType, int> calculateEvent();
    QPair<bool,int> calculateKillingEnemy(QPointF position);
    QPair<bool,int> calculateKillingHero();
    bool calculateKillingHeroByBullets(QPointF);
    QPair<bool,int> calculateCoints();
    QPair<bool,int> calculateBullets();
    QPair<EventType, QPointF> calcRoad(QPointF);

    void changeData(QPair<EventType, int>);
    std::unique_ptr<Model>& getModel() override;
private slots:
    void moveTimeHero();
    QTimer *timer;
     QTimer *MainTimer;
    //int timerId;
    QTimer *timerForAttack;
private:
    std::unique_ptr<FirstMenu> menu;
    std::unique_ptr<View> view_;
    std::unique_ptr<Model> model_;

};

#endif // PRESENTER_H
