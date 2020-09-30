#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //随机数相关
    srand((uint)time(nullptr));

    //创建控件
    QLineEdit *editMin = new QLineEdit("1");    //编辑最小值的输入框
    QLineEdit *editMax = new QLineEdit("10");   //编辑最大值的输入框
    editMin->setValidator(regExp);  //设置输入框的正则表达式，下同
    editMax->setValidator(regExp);
    setWidgetPointSize(editMin, 12);    //设置输入框的字体大小，下同
    setWidgetPointSize(editMax, 12);
    QLabel *label = new QLabel(" ~ ");  //"~"符号的Label
    setWidgetPointSize(label, 12);  //设置字体大小

    QPushButton *btnGen = new QPushButton("抽取");    //抽取按钮
    setWidgetPointSize(btnGen, 10); //设置字体大小

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

    connect(btnGen, &QPushButton::clicked, [=]{ //抽取按钮按下后触发的东西
        //在特定情况下将文本设置为"0"
        QString tmpText1 = editMin->text();
        QString tmpText2 = editMax->text();
        if(tmpText1.isEmpty() || tmpText1 == '-') {
            editMin->setText("0");
        }
        if(tmpText2.isEmpty() || tmpText2 == '-') {
            editMax->setText("0");
        }
\
        //得到最小值和最大值
        bool ok, hasErr = false;
        int valueMin = editMin->text().toInt(&ok);
        if(!ok) {
            QMessageBox::warning(this, "错误", "得到最小值失败\n可能是数字过大(n>" + QString::number(INT_MAX) + ")或过小(n<" + QString::number(INT_MIN) + ")");
            hasErr = true;
        }
        int valueMax = editMax->text().toInt(&ok);
        if(!ok) {
            QMessageBox::warning(this, "错误", "得到最大值失败\n可能是数字过大(n>" + QString::number(INT_MAX) + ")或过小(n<" + QString::number(INT_MIN) + ")");
            hasErr = true;
        }
        if(hasErr) return;

        //最小值不能大于最大值
        if(valueMin > valueMax) {
            QMessageBox::warning(this, "错误", "最小值不能大于最大值");
            return;
        }

        //得到结果
        long long offNum = (long long)valueMax - valueMin + 1;
        if(offNum > RAND_MAX + 1) {
            QMessageBox::warning(this, "错误", "取值范围超过了随机数的能力上限 (" + QString::number(RAND_MAX) + ")");
            return;
        }
        int result = valueMin + rand() % offNum;

        //显示消息
        QMessageBox::information(this, "结果", QString::number(result));
    });

    //创建布局
    QHBoxLayout *layTop = new QHBoxLayout;
    layTop->addWidget(editMin);
    layTop->addWidget(label);
    layTop->addWidget(editMax);

    QHBoxLayout *layBottom = new QHBoxLayout;
    layBottom->addStretch();
    layBottom->addWidget(btnGen);
    layBottom->addStretch();

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
}

Widget::~Widget()
{

}

template<typename T>void Widget::setWidgetPointSize(T *widget, int pointSize) {
    QFont font = widget->font();
    font.setPointSize(pointSize);
    widget->setFont(font);
}

