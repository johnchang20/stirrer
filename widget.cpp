#include "widget.h"
#include "ui_widget.h"
#include "digitbutton.h"
#include <QRegularExpression>
#include <QMouseEvent>
#include <QEvent>
#include <QLineEdit>
#include <QButtonGroup>
#include <QDebug>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <QString>
#include <string>
#include <iostream>
#include <QProcess>
#include <QStringList>

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
    /*选择框加入按钮组以后start, stop会默认变成单选 */
    group->setExclusive(true);

    /* power on, read EEPROM date and show in the rotation area*/
    QString eepromDataPath = "/sys/class/i2c-dev/i2c-0/device/0-0052/eeprom";
    QFile file(eepromDataPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open EEPROM file!";
        return;
    }
    QTextStream in(&file);
    QString eepromData = in.readAll(); //get all information from EEPROM
    file.close();

    /*get the rotation 1 ,2 ,3 information and show*/
    QString rotation1 = eepromData.mid(253, 3);
    rotation1.remove(QRegularExpression("^0+"));
    if (rotation1.isEmpty()) {
        rotation1 = "0"; // Ensure at least one zero remains
    }
    ui->input1->setText(rotation1);

    QString rotation2 = eepromData.mid(269, 3);
    rotation2.remove(QRegularExpression("^0+"));
    if (rotation2.isEmpty()) {
        rotation2 = "0"; // Ensure at least one zero remains
    }
    ui->input2->setText(rotation2);

    QString rotation3 = eepromData.mid(285, 3);
    rotation3.remove(QRegularExpression("^0+"));
    if (rotation3.isEmpty()) {
        rotation3 = "0"; // Ensure at least one zero remains
    }
    ui->input3->setText(rotation3);
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
    if(tmp < 10)
        data.prepend("00");
    else if((tmp >= 10 ) & (tmp < 100))
        data.prepend("0");

    /***call function "writeeeprom"******/
    std::string Executable_Program_Path = "/root/app/writeeeprom";
    std::string offset = "253";  //forbidden changing this value
    std::string ratationRPM = data.toStdString();
    std::string command = Executable_Program_Path + " " + offset + " " + ratationRPM ;
    int ret = system(command.c_str());
    // Check if the execution was successful
    if (ret == -1) {
        std::cerr << "Error: write rpm to eeprom failed!" << std::endl;
    } else {
        std::cout << "successful: write new rpm to eeprom completed!" << std::endl;
    }
}

void Widget::saveAllRotations2()
{
    QString data = ui->input2->text();
    int tmp = data.toInt();
    if(tmp < 10)
        data.prepend("00");
    else if((tmp >= 10 ) & (tmp < 100))
        data.prepend("0");

    /***call function "writeeeprom"******/
    std::string Executable_Program_Path = "/root/app/writeeeprom";
    std::string offset = "269";  //forbidden changing this value
    std::string ratationRPM = data.toStdString();
    std::string command = Executable_Program_Path + " " + offset + " " + ratationRPM ;
    int ret = system(command.c_str());
    // Check if the execution was successful
    if (ret == -1) {
        std::cerr << "Error: write rpm to eeprom failed!" << std::endl;
    } else {
        std::cout << "successful: write new rpm to eeprom completed!" << std::endl;
    }
}

void Widget::saveAllRotations3()
{
    QString data = ui->input3->text();
    int tmp = data.toInt();
    if(tmp < 10)
        data.prepend("00");
    else if((tmp >= 10 ) & (tmp < 100))
        data.prepend("0");

    /***call function "writeeeprom"******/
    std::string Executable_Program_Path = "/root/app/writeeeprom";
    std::string offset = "285";  //forbidden changing this value
    std::string ratationRPM = data.toStdString();
    std::string command = Executable_Program_Path + " " + offset + " " + ratationRPM ;
    int ret = system(command.c_str());
    // Check if the execution was successful
    if (ret == -1) {
        std::cerr << "Error: write rpm to eeprom failed!" << std::endl;
    } else {
        std::cout << "successful: write new rpm to eeprom completed!" << std::endl;
    }
}

void Widget::on_start_clicked()
{
    /*start motor rotate command format:
    system("/root/app/set3pwm rpm1 rpm2 rpm3");*/
    QString rotation1 = ui->input1->text();
    QString rotation2 = ui->input2->text();
    QString rotation3 = ui->input3->text();
    std::string rpm1 = rotation1.toStdString();
    std::string rpm2 = rotation2.toStdString();
    std::string rpm3 = rotation3.toStdString();

    std::string Executable_Program_Path = "/root/app/set3pwm";
    std::string command = Executable_Program_Path + " " + rpm1 + " " + rpm2 + " " + rpm3;
    int ret = system(command.c_str());
    // Check if the execution was successful
    if (ret == -1) {
        std::cerr << "Error: set3pwm failed!" << std::endl;
    } else {
        std::cout << "Successful: set3pwm completed!!!!" << std::endl;
    }
}

