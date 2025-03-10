#include "clickablelineedit.h"
#include <QLineEdit>

ClickableLineEdit::ClickableLineEdit(QWidget *parent)
    :QLineEdit(parent)
{

}

void ClickableLineEdit::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    QLineEdit::mousePressEvent(event);
}
