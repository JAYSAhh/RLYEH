
#include "BindWidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>

#ifndef R_LYEH_MAINWIDGET_H
#define R_LYEH_MAINWIDGET_H
#include "ComHandler.h"
#include <thread>

class MainWidget:public QWidget {
Q_OBJECT
public:
    MainWidget(int &height, int &width);
signals:
    void packageReceived(std::string &package);
    void startClicked(std::thread &thr);
private slots:
    void onSetClicked();
    void onPortChanged(std::string &port);
    void onStartClicked();
    void onStopClicked();
    void onClearClicked();
    void onPackage(QString package);
private:
    std::thread *_thread;
    std::string _port;
    ComHandler _handler;
    QPushButton *_startButton;
    QPushButton *_stopButton;
    BindWidget *_bind;
    QPushButton *_clearButton;
    QVBoxLayout *_layout;
    QTextEdit *_logBox;
};


#endif //R_LYEH_MAINWIDGET_H