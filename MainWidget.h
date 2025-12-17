#include <thread>
#include <QTextEdit>
#include "BindWidget.h"
#include "ComHandler.h"

#ifndef RLYEH_MAINWIDGET_H
#define RLYEH_MAINWIDGET_H


class MainWidget:public QWidget {
Q_OBJECT
public:
    MainWidget(int &height, int &width);
private slots:
    void clickedSlot();
    void portChangedSlot(std::string &port);
    void startClickedSlot();
    void stopClickedSlot();
    void clearClickedSlot();
    void getPackageSlot(QString package);
private:
    void initUI(int &height, int &weight);
    void setConnections();
    std::thread *_thread;
    std::string _port;
    ComHandler _handler;
    QPushButton *_start_button;
    QPushButton *_stop_button;
    BindWidget *_bind;
    QPushButton *_clear_button;
    QVBoxLayout *_layout;
    QTextEdit *_log_box;
};


#endif