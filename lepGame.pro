QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstract_presenter.cpp \
    coint.cpp \
    enemy.cpp \
    hero.cpp \
    main.cpp \
    map.cpp \
    model.cpp \
    presenter.cpp \
    view.cpp

HEADERS += \
    abstract_presenter.h \
    coint.h \
    enemy.h \
    hero.h \
    map.h \
    model.h \
    presenter.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
