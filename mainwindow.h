#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QAxWidget>
#include<QVBoxLayout>
#include<QDebug>
#include<QPushButton>
#include<ActiveQt>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<unordered_map>
#include<vector>
#include<queue>
#include"coordinate.h"
#include"road.h"
#include"mytime.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct cmp
{
    bool operator()(const Road& a,const Road& b)
    {
        return a.passedTimes>b.passedTimes;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //QAxWidget * axWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    //std::string taxiDatas[10357];


    void initBtn1();
    void initBtn2();
    void initBtn3();
    void initBtn4();
    void initBtn5();
    void initBtn6();
    void initBtn7();
    int findTaxi(int id,int startd,int endd,int starth,int endh,Coordinate ltpos,Coordinate rbpos);
    void addToTable(std::vector<std::string>& vec,std::unordered_map<std::string,int>& hashmap);
};
#endif // MAINWINDOW_H
