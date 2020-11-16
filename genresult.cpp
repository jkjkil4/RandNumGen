#include "genresult.h"

GenResult::GenResult(QVector<int> vResults, QWidget *parent) : QDialog(parent)
{
    //创建控件
    QPushButton *btnOK = new QPushButton("确认");
    connect(btnOK, &QPushButton::clicked, [=]{ close(); });
    listWidget->setMinimumSize(300, 500);
    listWidget->setMaximumSize(300, 500);


    //创建布局
    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->addStretch();
    layBottom->addWidget(btnOK);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addWidget(listWidget);
    layMain->addLayout(layBottom);
    setLayout(layMain);


    //设置数据
    int row = 1;
    for(int result : vResults) {
        QListWidgetItem *item = new QListWidgetItem(QString::number(row) + ":\t" + QString::number(result));
        listWidget->addItem(item);
        row++;
    }
}
