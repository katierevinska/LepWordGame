#ifndef PRESENTER_H
#define PRESENTER_H

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
        Coint, Enemy, Nothing, Road ,Bullet ,Attac, Killing
    };
    enum GameCode {
        Fail, Win, Go
    };
    GameCode code;
    void timerEvent(QTimerEvent *event) override;
    void moveEvents(QString str) override;
    void startGame(int) override;
    void GameOver();
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
    QPair<EventType, int> calcRoad();

    void changeData(QPair<EventType, int>);
    std::unique_ptr<Model>& getModel() override;
private slots:
    void moveTimeHero();
    QTimer *timer;
    int timerId;
    QTimer *timerForAttack;
private:
    std::unique_ptr<View> view_;
    std::unique_ptr<Model> model_;

};

#endif // PRESENTER_H
