#ifndef ABSTRACT_PRESENTER_H
#define ABSTRACT_PRESENTER_H

#include <QWidget>

class Model;
class abstract_presenter : public QWidget
{
public:
    virtual void startGame(int) = 0;
    virtual std::unique_ptr<Model>& getModel() = 0;
    virtual void moveEvents(QString str)=0;
    virtual ~abstract_presenter()
    { }
};

#endif // ABSTRACT_PRESENTER_H
