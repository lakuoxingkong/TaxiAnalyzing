#ifndef MYWIDGET2_H
#define MYWIDGET2_H

#include <QWidget>

namespace Ui {
class MyWidget2;
}

class MyWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget2(QWidget *parent = nullptr);
    ~MyWidget2();

private:
    Ui::MyWidget2 *ui;
};

#endif // MYWIDGET2_H
