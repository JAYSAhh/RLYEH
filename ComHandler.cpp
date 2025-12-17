#include "ComHandler.h"
#include <vector>
#include <thread>
#include <string>
#include  "MainWidget.h"

ComHandler::ComHandler() {
    _log = std::vector<std::string>();

    _dcb_serial_params = {0};
    _dcb_serial_params.BaudRate = CBR_9600;
    _dcb_serial_params.ByteSize = 8;
    _dcb_serial_params.Parity = EVENPARITY;
    _dcb_serial_params.StopBits = ONESTOPBIT;


    _timeouts = {0};
    _timeouts.ReadTotalTimeoutConstant = 300;
    _timeouts.ReadIntervalTimeout = 300;


    _buffer = std::vector<unsigned char>(256);
    _active =  new std::atomic_bool(false);
}
void ComHandler::LinkWindow(MainWidget &widget) {
    _widget = &widget;
}

bool ComHandler::SetPort(std::string &port) {
    std::string portName = "\\\\.\\COM" + port;
    HANDLE newPort = CreateFile(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    _com_port = newPort;
    if (newPort != INVALID_HANDLE_VALUE) {
        SetCommState(_com_port,&_dcb_serial_params);
        SetCommTimeouts(_com_port ,&_timeouts);
        return true;
    }
    else {
        return false;
    }

}

void ComHandler::StartRead() {
    std::cout<<"starting read\n";
    _active->store(true);
    std::cout<<"1g\n";
    while (_active->load()) {
        ReadFile(_com_port,_buffer.data(),256,&_red_bytes,0);
        if (_red_bytes != 0) {
            auto data = _buffer.data();
            std::string message_raw = std::string(reinterpret_cast<char*>(data));
            QString message = QString::fromStdString("[package] [bytes:"+ std::to_string(_red_bytes)+"] text: " + message_raw+"\n");
            emit packageReceived(message);
        }
    }
    std::cout<<"Ended \n";

}

void ComHandler::StopRead() {
    _active->store(false);
}





