#include "BindWidget.h"
#include <iostream>


void BindWidget::onSetClicked() {
    emit SetClicked();
}
void BindWidget::onPortChanged() {
    _port = _lineEdit->text().toStdString();
    emit PortChanged(_port);
}

BindWidget::BindWidget(QWidget *parent): QWidget(parent) {
    _lineEdit = new QLineEdit(this);
    _lineEdit->setPlaceholderText("COM PORT");
    _setButton =new QPushButton("SET",this);

    _layout = new QHBoxLayout(this);
    _layout->addWidget(_setButton);
    _layout->addWidget(_lineEdit);


    connect(_setButton,&QPushButton::clicked,this,&BindWidget::onSetClicked);
    connect(_lineEdit,&QLineEdit::textChanged,this,&BindWidget::onPortChanged);

    _setButton->setObjectName("set");

    this->setFixedHeight(60);
    this->setStyleSheet(QString("QPushButton{width:100px;margin-left:0px}QLineEdit{height:50px;margin-right:0px}#set{background-color:#385170}"));
}

