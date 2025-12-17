#include <iostream>
#include <QApplication>
#include <QWidget>
#include "MainWidget.h"
#include "ComHandler.h"
#include <thread>

void WidgetThread() {

}

int main(int argc, char *argv[]) {
    QApplication app = QApplication(argc,argv);
    int height = 600;
    int width = 400;
    MainWidget w = MainWidget(height,width);
    w.show();




    app.exec();
}