#ifndef RLYEH_BINDWIDGET_H
#define RLYEH_BINDWIDGET_H
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>



class BindWidget:public QWidget {
    Q_OBJECT
public:
    explicit  BindWidget (QWidget *parent = nullptr);
signals:
    void SetClicked();
    void PortChanged(std::string &port);
private slots:
    void onSetClicked();
    void onPortChanged();
private:
    void initUI();
    void setConnections();
    QLineEdit *_lineEdit;
    QPushButton *_setButton;
    QHBoxLayout *_layout;
    std::string _port;
};


#endif