#ifndef MYWIDGET6_H
#define MYWIDGET6_H

#include <QWidget>

namespace Ui {
class MyWidget6;
}

class MyWidget6 : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget6(QWidget *parent = nullptr);
    ~MyWidget6();

private:
    Ui::MyWidget6 *ui;
};

#endif // MYWIDGET6_H
