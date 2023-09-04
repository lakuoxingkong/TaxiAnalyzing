#ifndef MYWIDGET5_H
#define MYWIDGET5_H

#include <QWidget>

namespace Ui {
class MyWidget5;
}

class MyWidget5 : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget5(QWidget *parent = nullptr);
    ~MyWidget5();

private:
    Ui::MyWidget5 *ui;
};

#endif // MYWIDGET5_H
