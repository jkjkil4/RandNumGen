#ifndef GENDIALOG_H
#define GENDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

#include "header.h"

class GenDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GenDialog();
    ~GenDialog() override;

    bool isNoRepeat() { return cbbNoRepeat->isChecked(); }

private:
    QSpinBox *spinTimes = new QSpinBox;
    QCheckBox *cbbNoRepeat = new QCheckBox("不重复");
};

#endif // GENDIALOG_H
