#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //随机数相关
    srand((uint)time(nullptr));

    //创建控件
    editMin->setValidator(regExp);  //设置输入框的正则表达式，下同
    editMax->setValidator(regExp);
    setWidgetPointSize(editMin, 12);    //设置输入框的字体大小，下同
    setWidgetPointSize(editMax, 12);
    QLabel *label = new QLabel(" ~ ");  //"~"符号的Label
    setWidgetPointSize(label, 12);  //设置字体大小

    QPushButton *btnGen = new QPushButton("抽取");    //抽取按钮
    setWidgetPointSize(btnGen, 10); //设置字体大小

    QPushButton *btnGenMore = new QPushButton("抽取多次");

    QMenuBar *menuBar = new QMenuBar;
    {//菜单
        QMenu *menu = new QMenu("关于");
        menuBar->addMenu(menu);

        //关于作者
        QAction *actAbout = new QAction("关于作者");
        menu->addAction(actAbout);
        connect(actAbout, &QAction::triggered, [=]{
            QMessageBox::about(this, "关于作者",
                               "作者: jkjkil4<br>"
                               "github: <a href=https://github.com/jkjkil4/RandNumGen>https://github.com/jkjkil4/RandNumGen</a><br>"
                               "反馈问题: jkjkil@qq.com");
        });

        //关于Qt
        QAction *actAboutQt = new QAction("关于Qt");
        menu->addAction(actAboutQt);
        connect(actAboutQt, &QAction::triggered, [=]{
            QMessageBox::aboutQt(this);
        });
    }

    connect(btnGen, SIGNAL(clicked()), this, SLOT(onGen()));
    connect(btnGenMore, SIGNAL(clicked()), this, SLOT(onGenMore()));

    //创建布局
    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->addWidget(editMin);
    layTop->addWidget(label);
    layTop->addWidget(editMax);

    QHBoxLayout *layGenMore = new QHBoxLayout;
    layGenMore->addStretch();
    layGenMore->addWidget(btnGenMore);

    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->addStretch(1);
    layBottom->addWidget(btnGen);
    layBottom->addLayout(layGenMore, 1);

    QVBoxLayout *layCentral = new QVBoxLayout;
    layCentral->addLayout(layTop);
    layCentral->addLayout(layBottom);
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layCentral);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->setMargin(0);
    layMain->addWidget(menuBar);
    layMain->addWidget(centralWidget);

    //设置窗口属性
    setLayout(layMain);
    adjustSize();
    setMaximumSize(size());
    setMinimumSize(size());
    setWindowTitle("随机数生成器");

    //读取设置
    QSettings config(APP_DIR + "/config.ini", QSettings::IniFormat);
    editMin->setText(config.value("value/min", 1).toString());
    editMax->setText(config.value("value/max", 10).toString());
}

Widget::~Widget()
{
    QSettings config(APP_DIR + "/config.ini", QSettings::IniFormat);
    config.setValue("value/min", editMin->text());
    config.setValue("value/max", editMax->text());
}

bool Widget::getValue(int &valueMin, int &valueMax) {
    //在特定情况下将文本设置为"0"
    QString tmpText1 = editMin->text();
    QString tmpText2 = editMax->text();
    if(tmpText1.isEmpty() || tmpText1 == '-') {
        editMin->setText("0");
    }
    if(tmpText2.isEmpty() || tmpText2 == '-') {
        editMax->setText("0");
    }

    //得到最小值和最大值
    bool ok, hasErr = false;
    int tmpValueMin = editMin->text().toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "错误", "得到最小值失败\n可能是数字过大(n>" + QString::number(INT_MAX) + ")或过小(n<" + QString::number(INT_MIN) + ")");
        hasErr = true;
    }
    int tmpValueMax = editMax->text().toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "错误", "得到最大值失败\n可能是数字过大(n>" + QString::number(INT_MAX) + ")或过小(n<" + QString::number(INT_MIN) + ")");
        hasErr = true;
    }
    if(hasErr) return false;

    valueMin = tmpValueMin;
    valueMax = tmpValueMax;
    return true;
}

bool Widget::check(int min, int max, QString *err) {
    //最小值不能大于最大值
    if(min > max) {
        if(err)
            *err = "最小值不能大于最大值";
        return false;
    }

    //得到结果
    long long offNum = (long long)max - min + 1;
    if(offNum > RAND_MAX + 1) {
        if(err)
            *err = "取值范围超过了随机数的能力上限 (" + QString::number(RAND_MAX) + ")";
        return false;
    }
    return true;
}

int Widget::randNum(int min, int max) {
    long long offNum = (long long)max - min + 1;
    return min + rand() % offNum;
}

void Widget::onGen() {
    int valueMin = 0, valueMax = 0;
    if(getValue(valueMin, valueMax)) {
        QString err;
        if(check(valueMin, valueMax, &err)) {
            int result = randNum(valueMin, valueMax);
            QMessageBox::information(this, "结果", QString::number(result), "确定");
        } else {
            QMessageBox::warning(this, "错误", err);
        }
    }
}

void Widget::onGenMore() {
    int valueMin = 0, valueMax = 0;
    if(getValue(valueMin, valueMax)) {
        QString err;
        if(check(valueMin, valueMax, &err)) {
            GenDialog dialog;
            int times = dialog.exec();
            qDebug() << times;
            if(times) {
                bool isNoRepeat = dialog.isNoRepeat();
                long long offNum = (long long)valueMax - valueMin + 1;
                if(isNoRepeat && times > offNum) {
                    QMessageBox::warning(this, "错误", "若勾选了 \"不重复\"\n抽取数量不能大于可抽取数量");
                    return;
                }
                QVector<int> vResults;
                for(int i = 0; i < times; i++) {
                    int result = randNum(valueMin, valueMax);
                    if(isNoRepeat && vResults.contains(result)) {
                        i--;
                        continue;
                    }
                    vResults << result;
                }
                GenResult genResult(vResults);
                genResult.exec();
            }
        } else {
            QMessageBox::warning(this, "错误", err);
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *ev) {
    if(ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return) {
        onGen();
        ev->ignore();
    }
}

template<typename T>void Widget::setWidgetPointSize(T *widget, int pointSize) {
    QFont font = widget->font();
    font.setPointSize(pointSize);
    widget->setFont(font);
}

