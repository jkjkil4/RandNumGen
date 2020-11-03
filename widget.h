#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QSettings>
#include <QCoreApplication>

#include <QRegExpValidator>
#include <QMessageBox>

#define APP_DIR QCoreApplication::applicationDirPath()

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

    QLineEdit *editMin = new QLineEdit("1");    //编辑最小值的输入框
    QLineEdit *editMax = new QLineEdit("10");   //编辑最大值的输入框
};

#endif // WIDGET_H
