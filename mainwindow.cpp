#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenu>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->takeCentralWidget();
    this->setCentralWidget(ui->widget1);//初始显示widget1，即显示轨迹




    //菜单栏“选择功能”下点击“显示轨迹”，将中心窗体换成widget1
    connect(ui->action1,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget1);
        //ui->widget2->setVisible(true);
    });

    //点击“区域范围查询”
    connect(ui->action2,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget2);
        //ui->widget2->setVisible(true);
    });

    //点击“区域关联分析1”
    connect(ui->action4,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget4);
        //ui->widget2->setVisible(true);
    });

    //点击“区域关联分析2”
    connect(ui->action5,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget5);
        //ui->widget2->setVisible(true);
    });

    //点击“频繁路径分析”
    connect(ui->action6,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget6);
        //ui->widget2->setVisible(true);
    });

    //点击“通信时间分析”
    connect(ui->action7,&QAction::triggered,this,[=](){
        this->takeCentralWidget();
        this->setCentralWidget(ui->widget7);
        //ui->widget2->setVisible(true);
    });


}



MainWindow::~MainWindow()
{
    delete ui;
}

