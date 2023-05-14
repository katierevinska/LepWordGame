#ifndef PRESENTER_H
#define PRESENTER_H

#include "model.h"
#include "view.h"
#include "abstract_presenter.h"
#include<memory>
#include<QTimer>
#include<QPair>

class Presenter : public abstract_presenter
{
public:
    Presenter();
    enum EventType{
        Coint, Enemy, Nothing
    };
    enum GameCode {
        Fail, Win
    };
    void timerEvent(QTimerEvent *event) override;
    void moveEvents(QString str) override;
    void startGame(int) override;
    void GameOver();
    void setLevel(int);
    QPair<EventType, int> calculateEvent();
    void changeData(QPair<EventType, int>);
    std::unique_ptr<Model>& getModel() override;
private slots:
 void moveHero();
    QTimer *timer;
    int timerId;
    std::vector<QPoint> trajectory{{},{}};//Trajectory
    void setTrajectory(QString);
private:
 std::unique_ptr<View> view_;
 std::unique_ptr<Model> model_;

};

#endif // PRESENTER_H
