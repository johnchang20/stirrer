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

void digitButton::on_back_clicked()
{
    this->close();
}

void digitButton::on_ok_clicked()
{
    emit sendNumber(ui->input_area->text());    // Emit signal with the text
    emit saveParaments();   // Emit signal saveParaments
    this->close();
}

void digitButton::on_clear_clicked()
{
    ui->input_area->clear();
}

void digitButton::on_zero0_clicked()
{
    ui->input_area->insert("0");
    judge_value();
}

void digitButton::on_one1_clicked()
{
    ui->input_area->insert("1");
    judge_value();
}

void digitButton::on_two2_clicked()
{
    ui->input_area->insert("2");
    judge_value();
}

void digitButton::on_three3_clicked()
{
    ui->input_area->insert("3");
    judge_value();
}

void digitButton::on_four4_clicked()
{
    ui->input_area->insert("4");
    judge_value();
}

void digitButton::on_five5_clicked()
{
    ui->input_area->insert("5");
    judge_value();
}

void digitButton::on_six6_clicked()
{
    ui->input_area->insert("6");
    judge_value();
}

void digitButton::on_seven7_clicked()
{
    ui->input_area->insert("7");
    judge_value();
}

void digitButton::on_eight8_clicked()
{
    ui->input_area->insert("8");
    judge_value();
}

void digitButton::on_nine9_clicked()
{
    ui->input_area->insert("9");
    judge_value();
}

void digitButton::judge_value()
{
    int value = ui->input_area->text().toInt();
    if(value > 120){
        warning *newWindow = new warning();
        newWindow->move(400,200);
        newWindow->show();
        ui->input_area->clear();
    }
}

