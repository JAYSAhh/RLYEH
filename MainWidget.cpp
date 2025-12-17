#include "MainWidget.h"
#include <thread>
#include  "ComHandler.h"


MainWidget::MainWidget(int &height, int &weight): _handler() {
    MainWidget *widget = this;
    _handler.LinkWindow(*widget);
    _port = "10";

    initUI(height,weight);
    setConnections();
}

void MainWidget::clickedSlot() {
    std::cout<<"clicked\n";
    _handler.StopRead();
    _handler.SetPort(_port);
}
void MainWidget::portChangedSlot(std::string &port) {
    _port = port;
}

void MainWidget::startClickedSlot() {
    std::cout<<"start clicked\n";
    _thread = new std::thread(&ComHandler::StartRead,&_handler);
    _thread->detach();
}
void MainWidget::stopClickedSlot() {
    std::cout<<"stop clcked\n";
    _handler.StopRead();
}
void MainWidget::clearClickedSlot() {
    _log_box->setText("");
}

void MainWidget::getPackageSlot(QString package) {
    std::cout<<"got\n";
    auto current_text = _log_box->toPlainText();
    _log_box->setText(current_text+ package);
}

void MainWidget::initUI(int &height, int &weight) {
    _bind = new  BindWidget(this);
    _start_button =new QPushButton("START",this);
    _stop_button =new QPushButton("STOP",this);
    _clear_button = new QPushButton("CLEAR",this);
    _layout = new QVBoxLayout(this);
    _log_box = new QTextEdit(this);
    _log_box->setFixedHeight(300);
    _log_box->setReadOnly(true);

    _start_button->setStyleSheet(QString("QPushButton{background-color:#cbf078;color:white}QPushButton:hover{background-color:white;color:black}"));
    _stop_button->setStyleSheet(QString("QPushButton{background-color:#e46161;color:white}QPushButton:hover{background-color:white;color:black}"));
    _clear_button->setStyleSheet(QString("QPushButton{background-color:#61c0bf;color:white}QPushButton:hover{background-color:white;color:black}"));

    _layout->addWidget(_bind);
    _layout->addWidget(_start_button);
    _layout->addWidget(_stop_button);
    _layout->addWidget(_log_box);
    _layout->addWidget(_clear_button);

    this->setWindowTitle("Rlyeh");
    this->setWindowIcon(QIcon(":/love.ico"));
    this->setFixedHeight(height);
    this->setFixedWidth(weight);
    const QString sheet= "BindWidget{margin:0} *{margin:0;font-size:20px;position:flex} QPushButton:hover{background-color:white;color:black} MainWidget{background-color:#ececec;}QPushButton{margin-left:10px;margin-right:10px;color:white;border-radius:5px;height:50px;border:2px solid;border-color:#142d4c;}QLineEdit{height:60px;border:2px solid;border-radius:5px}";

    this->setStyleSheet(sheet);
}

void MainWidget::setConnections() {
    connect(_bind,&BindWidget::SetClicked,this, &MainWidget::clickedSlot);
    connect(_bind,&BindWidget::PortChanged,this,&MainWidget::portChangedSlot);
    connect(_start_button,&QPushButton::clicked,this,&MainWidget::startClickedSlot );
    connect(_stop_button,&QPushButton::clicked,this,&MainWidget::stopClickedSlot);
    connect(_clear_button,&QPushButton::clicked,this,&MainWidget::clearClickedSlot);

    connect(&_handler,&ComHandler::packageReceived,this,&MainWidget::getPackageSlot);

}

