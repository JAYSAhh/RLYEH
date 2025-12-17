#include <QApplication>
#include "MainWidget.h"


int main(int argc, char *argv[]) {
    QApplication app = QApplication(argc,argv);
    int height = 600;
    int width = 400;
    MainWidget w = MainWidget(height,width);
    w.show();




    app.exec();
}