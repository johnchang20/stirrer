#ifndef DIGITBUTTON_H
#define DIGITBUTTON_H

#include <QWidget>
#include <QObject>

namespace Ui {
class digitButton;
}

class digitButton : public QWidget
{
    Q_OBJECT

public:
    explicit digitButton(QWidget *parent = nullptr);
    ~digitButton();

private slots:
    void on_back_clicked();
    void on_ok_clicked();
    void on_clear_clicked();
    void on_zero0_clicked();
    void on_one1_clicked();
    void on_two2_clicked();
    void on_three3_clicked();
    void on_four4_clicked();
    void on_five5_clicked();
    void on_six6_clicked();
    void on_seven7_clicked();
    void on_eight8_clicked();
    void on_nine9_clicked();

signals:
    void sendNumber(const QString &number);  // Signal to send data

private:
    Ui::digitButton *ui;
};

#endif // DIGITBUTTON_H
