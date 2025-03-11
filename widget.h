#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "digitbutton.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class digitButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void openNewWindow1();
    void openNewWindow2();
    void openNewWindow3();

public slots:
    void receiveNumber1(const QString &number);  // Slot to receive data
    void receiveNumber2(const QString &number);  // Slot to receive data
    void receiveNumber3(const QString &number);  // Slot to receive data

private:
    Ui::Widget *ui;
    digitButton *digitButtonxx;
};





#endif // WIDGET_H
