#ifndef MYWIDGET7_H
#define MYWIDGET7_H

#include <QWidget>

namespace Ui {
class MyWidget7;
}

class MyWidget7 : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget7(QWidget *parent = nullptr);
    ~MyWidget7();

private:
    Ui::MyWidget7 *ui;
};

#endif // MYWIDGET7_H
