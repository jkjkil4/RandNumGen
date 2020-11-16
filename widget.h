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
#include <QKeyEvent>

#include <QRegExpValidator>
#include <QMessageBox>

#include <QDebug>

#include "header.h"
#include "gendialog.h"
#include "genresult.h"

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *ev) override;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() override;

    template<typename T>void setWidgetPointSize(T *widget, int pointSize);

    bool getValue(int& valueMin, int& valueMax);
    bool check(int min, int max, QString* err = nullptr);
    int randNum(int min, int max);

private slots:
    void onGen();
    void onGenMore();

private:
    //正则表达式
    QRegExpValidator *regExp = new QRegExpValidator(QRegExp("[-]{0,1}[0-9]{10}"), this);

    QLineEdit *editMin = new QLineEdit("1");    //编辑最小值的输入框
    QLineEdit *editMax = new QLineEdit("10");   //编辑最大值的输入框
};

#endif // WIDGET_H
