#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QRegExpValidator>
#include <QMessageBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    template<typename T>void setWidgetPointSize(T *widget, int pointSize);

private:
    //正则表达式
    QRegExpValidator *regExp = new QRegExpValidator(QRegExp("[-]{0,1}[0-9]{10}"), this);
};

#endif // WIDGET_H
