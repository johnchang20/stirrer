#include "widget.h"
#include "ui_widget.h"
#include "digitbutton.h"

#include <QMouseEvent>
#include <QEvent>
#include <QLineEdit>
#include <QButtonGroup>
#include <QDebug>
#include <iostream>

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
    connect(newWindow, SIGNAL(saveParaments()) ,this, SLOT(saveAllRotations1()));
}

void Widget::openNewWindow2()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
    // Connect signal from WidgetA to slot in WidgetB
    connect(newWindow, SIGNAL(sendNumber(const QString)) ,this, SLOT(receiveNumber2(const QString)));
    connect(newWindow, SIGNAL(saveParaments()) ,this, SLOT(saveAllRotations2()));
}

void Widget::openNewWindow3()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
    // Connect signal from WidgetA to slot in WidgetB
    connect(newWindow, SIGNAL(sendNumber(const QString)) ,this, SLOT(receiveNumber3(const QString)));
    connect(newWindow, SIGNAL(saveParaments()) ,this, SLOT(saveAllRotations3()));
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

void Widget::saveAllRotations1()
{
    QString data = ui->input1->text();
    /*add "0" at the head of string, as easy to understand with command hexdump -C eeprom*/
    int tmp = data.toInt();
    if(tmp < 100)
        data.prepend("0");

    QString eepromPath = "/sys/class/i2c-dev/i2c-0/device/0-0052/eeprom";  // EEPROM file path
    QFile file(eepromPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       file.seek(253);
       QTextStream out(&file);
       out << data;
       file.close();
       std::cout << "Data written to EEPROM successfully!\n";
    } else {
       std::cerr << "Failed to write to EEPROM!\n";
    }
}

void Widget::saveAllRotations2()
{
    QString data = ui->input2->text();
    int tmp = data.toInt();
    if(tmp < 100)
        data.prepend("0");

    QString eepromPath = "/sys/class/i2c-dev/i2c-0/device/0-0052/eeprom";  // EEPROM file path
    QFile file(eepromPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       file.seek(269);
       QTextStream out(&file);
       out << data;
       file.close();
       std::cout << "Data written to EEPROM successfully!\n";
    } else {
       std::cerr << "Failed to write to EEPROM!\n";
    }
}

void Widget::saveAllRotations3()
{
    QString data = ui->input3->text();
    int tmp = data.toInt();
    if(tmp < 100)
        data.prepend("0");

    QString eepromPath = "/sys/class/i2c-dev/i2c-0/device/0-0052/eeprom";  // EEPROM file path
    QFile file(eepromPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
       file.seek(285);
       QTextStream out(&file);
       out << data;
       file.close();
       std::cout << "Data written to EEPROM successfully!\n";
    } else {
       std::cerr << "Failed to write to EEPROM!\n";
    }
}
