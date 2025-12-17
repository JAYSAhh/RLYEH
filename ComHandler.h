#ifndef RLYEH_COMHANDLER_H
#define RLYEH_COMHANDLER_H
#include <iostream>
#include <vector>
#include <windows.h>
#include <QObject>
#include <qobjectdefs.h>



class MainWidget;

class ComHandler: public QObject {
    Q_OBJECT
public:
    ComHandler();
    void LinkWindow(MainWidget &widget);
    bool SetPort(std::string &port);
    void StartRead();
    void StopRead();

signals:
    void packageReceived(QString string);
private:

    HANDLE _com_port;
    DCB _dcb_serial_params;
    std::vector<unsigned char> _buffer;
    DWORD _red_bytes;
    COMMTIMEOUTS _timeouts;
    std::vector<std::string> _log;
    std::atomic_bool *_active;
    MainWidget *_widget;
};


#endif