#ifndef DIGITBUTTON_H
#define DIGITBUTTON_H

#include <QWidget>

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
    void on_pushButton_2_clicked();

private:
    Ui::digitButton *ui;
};

#endif // DIGITBUTTON_H
