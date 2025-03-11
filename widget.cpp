#include "widget.h"
#include "ui_widget.h"
#include "digitbutton.h"

#include <QMouseEvent>
#include <QEvent>
#include <QLineEdit>
#include <QButtonGroup>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*monitor the input area,if the mouse clicked or not */
    ui->input1 ->installEventFilter(this);
    ui->input2 ->installEventFilter(this);
    ui->input3 ->installEventFilter(this);

    /*将UI中创建好的选择框全部加入按钮组  */
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->start);
    group->addButton(ui->stop);
    /*选择框加入按钮组以后会默认变成单选 */
    group->setExclusive(true);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->input1 && event->type() == QEvent::MouseButtonPress) {
        openNewWindow1();
        return true;
    }
    if (obj == ui->input2 && event->type() == QEvent::MouseButtonPress) {
        openNewWindow2();
        return true;
    }
    if (obj == ui->input3 && event->type() == QEvent::MouseButtonPress) {
        openNewWindow3();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void Widget::openNewWindow1()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
    // Connect signal from WidgetA to slot in WidgetB
    connect(newWindow, SIGNAL(sendNumber(const QString)) ,this, SLOT(receiveNumber1(const QString)));
}

void Widget::openNewWindow2()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
    // Connect signal from WidgetA to slot in WidgetB
    connect(newWindow, SIGNAL(sendNumber(const QString)) ,this, SLOT(receiveNumber2(const QString)));
}

void Widget::openNewWindow3()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
    // Connect signal from WidgetA to slot in WidgetB
    connect(newWindow, SIGNAL(sendNumber(const QString)) ,this, SLOT(receiveNumber3(const QString)));
}

void Widget::receiveNumber1(const QString &number) {
    ui->input1->setText(number);  // Update QLineEdit with received number
}

void Widget::receiveNumber2(const QString &number) {
    ui->input2->setText(number);  // Update QLineEdit with received number
}

void Widget::receiveNumber3(const QString &number) {
    ui->input3->setText(number);  // Update QLineEdit with received number
}



