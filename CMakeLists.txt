cmake_minimum_required(VERSION 3.21)
project(menu_demo)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

include_directories(.)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(lepGame
        abstract_presenter.cpp
        abstract_presenter.h
        coint.cpp
        coint.h
        enemy.cpp
        enemy.h
        hero.cpp
        hero.h
        main.cpp
        map.cpp
        map.h
        model.cpp
        model.h
        presenter.cpp
        presenter.h
        trajectory.cpp
        trajectory.h
        view.cpp
        view.h)
target_link_libraries(lepGame
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
