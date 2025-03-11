#ifndef WARNING_H
#define WARNING_H

#include <QWidget>

namespace Ui {
class warning;
}

class warning : public QWidget
{
    Q_OBJECT

public:
    explicit warning(QWidget *parent = nullptr);
    ~warning();

private:
    Ui::warning *ui;
};

#endif // WARNING_H
