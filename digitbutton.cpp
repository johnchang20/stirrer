#include "digitbutton.h"
#include "ui_digitbutton.h"

digitButton::digitButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::digitButton)
{
    ui->setupUi(this);
}

digitButton::~digitButton()
{
    delete ui;
}

void digitButton::on_pushButton_2_clicked()
{
    this->close();
}
