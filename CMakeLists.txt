cmake_minimum_required(VERSION 3.26)
project(RLYEH)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/C++/QT/msvc2017_64")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(RLYEH main.cpp
        MainWidget.cpp
        MainWidget.h
        BindWidget.cpp
        BindWidget.h
        love.ico
        ComHandler.cpp
        ComHandler.h)

target_link_libraries(RLYEH Qt5::Core Qt5::Widgets)
