#ifndef CLICKABLELINEEDIT_H
#define CLICKABLELINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class ClickableLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ClickableLineEdit();
    explicit ClickableLineEdit(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked(); // Define a new signal
};


#endif // CLICKABLELINEEDIT_H
