#ifndef MYWIDGET4_H
#define MYWIDGET4_H

#include <QWidget>

namespace Ui {
class MyWidget4;
}

class MyWidget4 : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget4(QWidget *parent = nullptr);
    ~MyWidget4();

private:
    Ui::MyWidget4 *ui;
};

#endif // MYWIDGET4_H
