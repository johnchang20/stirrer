#include "widget.h"
#include "ui_widget.h"
#include "digitbutton.h"

#include <QMouseEvent>
#include <QEvent>
#include <QLineEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->input1 ->installEventFilter(this);
    ui->input2 ->installEventFilter(this);
    ui->input3 ->installEventFilter(this);
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
