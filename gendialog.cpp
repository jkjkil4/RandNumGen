#include "gendialog.h"

GenDialog::GenDialog()
{
    //创建控件
    QLabel *labTimes = new QLabel("次数: ");
    spinTimes->setRange(1, 100);
    QPushButton *btnOK = new QPushButton("确定");
    QPushButton *btnCancel = new QPushButton("取消");


    //信号与槽
    connect(btnOK, &QPushButton::clicked, [=]{ done(spinTimes->value()); });
    connect(btnCancel, &QPushButton::clicked, [=]{ reject(); });


    //创建布局
    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->addWidget(labTimes);
    layTop->addWidget(spinTimes);
    layTop->addSpacing(60);
    layTop->addWidget(cbbNoRepeat);

    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->addStretch();
    layBottom->addWidget(btnOK);
    layBottom->addWidget(btnCancel);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addLayout(layTop);
    layMain->addSpacing(10);
    layMain->addLayout(layBottom);
    setLayout(layMain);


    //读取设置
    QSettings config(APP_DIR + "/config.ini", QSettings::IniFormat);
    spinTimes->setValue(config.value("more/times", 1).toInt());
    cbbNoRepeat->setChecked(config.value("more/norepeat", true).toBool());
}

GenDialog::~GenDialog() {
    //保存设置
    QSettings config(APP_DIR + "/config.ini", QSettings::IniFormat);
    config.setValue("more/times", spinTimes->value());
    config.setValue("more/norepeat", cbbNoRepeat->isChecked());
}
