//
// Created by SACHAKAMEN on 12/15/2025.
//

#include "MainWidget.h"
#include <thread>
#include  "ComHandler.h"



void MainWidget::onSetClicked() {
    std::cout<<"clicked\n";
    _handler.StopRead();
    _handler.SetPort(_port);
}
void MainWidget::onPortChanged(std::string &port) {
    _port = port;
}

void MainWidget::onStartClicked() {
    std::cout<<"start clicked\n";
    _thread = new std::thread(&ComHandler::StartRead,&_handler);
    _thread->detach();
}
void MainWidget::onStopClicked() {
    std::cout<<"stop clcked\n";
    _handler.StopRead();
}
void MainWidget::onClearClicked() {
    _logBox->setText("");
}

void MainWidget::onPackage(QString package) {
    std::cout<<"got\n";
    auto current_text = _logBox->toPlainText();
    _logBox->setText(current_text+ package);
}



MainWidget::MainWidget(int &height, int &weight): _handler() {
    MainWidget *widget = this;
    _handler.LinkWindow(*widget);
    _port = "10";
    _bind = new  BindWidget(this);
    _startButton =new QPushButton("START",this);
    _stopButton =new QPushButton("STOP",this);
    _clearButton = new QPushButton("CLEAR",this);
    _layout = new QVBoxLayout(this);
    _logBox = new QTextEdit(this);
    _logBox->setFixedHeight(300);
    _logBox->setReadOnly(true);

    _startButton->setObjectName("start");
    _stopButton->setObjectName("stop");
    _clearButton->setObjectName("clear");

    _layout->addWidget(_bind);
    _layout->addWidget(_startButton);
    _layout->addWidget(_stopButton);
    _layout->addWidget(_logBox);
    _layout->addWidget(_clearButton);


    connect(_bind,&BindWidget::SetClicked,this, &MainWidget::onSetClicked);
    connect(_bind,&BindWidget::PortChanged,this,&MainWidget::onPortChanged);
    connect(_startButton,&QPushButton::clicked,this,&MainWidget::onStartClicked );
    connect(_stopButton,&QPushButton::clicked,this,&MainWidget::onStopClicked);
    connect(_clearButton,&QPushButton::clicked,this,&MainWidget::onClearClicked);

    connect(&_handler,&ComHandler::packageReceived,this,&MainWidget::onPackage);

    this->setWindowTitle("Rlyeh");
    this->setWindowIcon(QIcon(":/love.ico"));
    this->setFixedHeight(height);
    this->setFixedWidth(weight);
    const QString sheet= "BindWidget{margin:0} #clear{background-color:#385170}   *{margin:0;font-size:20px;position:flex} MainWidget{background-color:#ececec;}QPushButton{margin-left:10px;margin-right:10px;color:white;border-radius:5px;height:50px;border:2px solid;border-color:#142d4c;}QLineEdit{height:60px;border:2px solid;border-radius:5px} #stop{background-color:#DC143C}#start{background-color:#9fd3c7}";

    this->setStyleSheet(sheet);
}
