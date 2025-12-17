//
// Created by SACHAKAMEN on 12/15/2025.
//

#ifndef PARA5_COMHANDLER_H
#define PARA5_COMHANDLER_H
#include <windows.h>
#include <iostream>
#include <QObject>
#include <qobjectdefs.h>
#include <vector>
#include <thread>


class MainWidget;

class ComHandler: public QObject {
    Q_OBJECT
public:
    ComHandler();
    void LinkWindow(MainWidget &widget);
    bool SetPort(std::string &port);
    void StopRead();
    void StartRead();

signals:
    void packageReceived(QString string);
private:

    HANDLE _com_port;
    DCB _dcbSerialParams;
    std::vector<unsigned char> _buffer;
    DWORD _red_bytes;
    COMMTIMEOUTS _timeouts;
    std::vector<std::string> _log;
    std::atomic_bool *_active;
    MainWidget *_widget;
};


#endif //PARA5_COMHANDLER_H