#include "widget.h"
#include "ui_widget.h"
#include "digitbutton.h"

#include <QMouseEvent>
#include <QEvent>
#include <QLineEdit>
#include <QButtonGroup>

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
        openNewWindow();
        return true;
    }
    if (obj == ui->input2 && event->type() == QEvent::MouseButtonPress) {
        openNewWindow();
        return true;
    }
    if (obj == ui->input3 && event->type() == QEvent::MouseButtonPress) {
        openNewWindow();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void Widget::openNewWindow()
{
    digitButton *newWindow = new digitButton();
    newWindow->show();
}



