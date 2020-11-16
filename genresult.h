#ifndef GENRESULT_H
#define GENRESULT_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>

#include <QHBoxLayout>
#include <QVBoxLayout>

class GenResult : public QDialog
{
    Q_OBJECT
public:
    explicit GenResult(QVector<int> vResults, QWidget *parent = nullptr);
    ~GenResult() override = default;

private:
    QListWidget *listWidget = new QListWidget;
};

#endif // GENRESULT_H
