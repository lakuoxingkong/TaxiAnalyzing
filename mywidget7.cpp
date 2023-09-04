#include "mywidget7.h"
#include "ui_mywidget7.h"
#include"coordinate.h"
#include"mytime.h"
#include<stdio.h>
#include<fstream>
#include<string>
#include<QMessageBox>
#include<vector>

MyWidget7::MyWidget7(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget7)
{
    ui->setupUi(this);

    connect(ui->btn7,&QPushButton::clicked,[=]()
    {
        bool isInputCorrect[12];//标示输入框中内容是否正确
        int minTravelTime=1e9;//记录最短行车时间
        std::vector<std::string> bestRoads;//记录最快路段
        Coordinate ltPos1(ui->lineEdit2->text().toDouble(isInputCorrect),ui->lineEdit3->text().toDouble(isInputCorrect+1));//矩形区域1左上、右下坐标
        Coordinate rbPos1(ui->lineEdit2_2->text().toDouble(isInputCorrect+2),ui->lineEdit3_2->text().toDouble(isInputCorrect+3));
        Coordinate ltPos2(ui->lineEdit2_3->text().toDouble(isInputCorrect+4),ui->lineEdit3_3->text().toDouble(isInputCorrect+5));//矩形区域2左上、右下坐标
        Coordinate rbPos2(ui->lineEdit2_4->text().toDouble(isInputCorrect+6),ui->lineEdit3_4->text().toDouble(isInputCorrect+7));
        int requestStartDay=ui->lineEdit4_1->text().toInt(isInputCorrect+8),requestStartHour=ui->lineEdit4_2->text().toInt(isInputCorrect+9);//查询的开始日、时
        int requestEndDay=ui->lineEdit4_3->text().toInt(isInputCorrect+10),requestEndHour=ui->lineEdit4_4->text().toInt(isInputCorrect+11);//查询的结束日、时
        for(int i=0;i<12;++i)
        {
            if(!isInputCorrect[i])
            {
                QMessageBox::warning(this,"警告","非法输入");
                return;
            }
        }
        //输入正确
        char roadName[40];
        std::string line;

        for(int taxiNum=1;taxiNum<=1000;++taxiNum)
        {
            Time visitedTime;// 经过指定区域的时刻
            std::vector<std::string> passedRoads;//记录本车本次路径中途径的路段
            bool visited1=false,visited2=false;//一开始设置区域1，2均未访问
            //文件路径格式："D:\\Qt\\Projects\\Learn0219\\taxi_log_2008_by_id\\"+车号+"\\"+日时.txt
            char path[100],path0[100];
            sprintf(path0,"D:\\myTaxiData\\%d\\",taxiNum);
            if(requestStartDay==requestEndDay)
            {//查询开始、结束在同一天
                for(int y=requestStartHour;y<=requestEndHour;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);//拼接文件名
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件，无此记录则跳过
                            continue;
                        }
                    double longitude,latitude;
                    int day,hour,minute,second;
                    int travelTime;
                    while(std::getline(file,line))
                    {
                        //扫描文件每一行，得到经纬度、路名
                        sscanf(line.c_str(),"%d %d:%d:%d,%lf,%lf %s",&day,&hour,&minute,&second,&longitude,&latitude,roadName);
                        Coordinate currPos(longitude,latitude);//现在位置
                        Time currTime(day,hour,minute,second);//现在时刻
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {//在区域1
                            visited1=true;//设置区域1已访问
                            if(visited2==true)
                            {//先前已访问过区域2
                                visited2=false;//设置区域2未访问
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {//在区域2
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else
                        {//不在区域1或2
                            if(visited1||visited2)
                            {//先前已访问区域1或2，则记录路径
                                std::string rm(roadName);
                                if(passedRoads.empty()||passedRoads[passedRoads.size()-1]!=rm)
                                {//现在所处道路与上一条记录所在道路不是同一条，则加入容器passedRoads
                                    passedRoads.push_back(rm);
                                }
                            }
                        }

                    }
                    file.close();
                }
            }
            else//查询开始结束不在同一天
            {
                //第一天
                for(int y=requestStartHour;y<=23;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);//拼接文件名
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件，无此记录则跳过
                            continue;
                        }
                    double longitude,latitude;
                    int day,hour,minute,second;
                    int travelTime;
                    while(std::getline(file,line))
                    {
                        //扫描文件每一行，得到经纬度、路名
                        sscanf(line.c_str(),"%d %d:%d:%d,%lf,%lf %s",&day,&hour,&minute,&second,&longitude,&latitude,roadName);
                        Coordinate currPos(longitude,latitude);//现在位置
                        Time currTime(day,hour,minute,second);//现在时刻
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {//在区域1
                            visited1=true;//设置区域1已访问
                            if(visited2==true)
                            {//先前已访问过区域2
                                visited2=false;//设置区域2未访问
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {//在区域2
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else
                        {//不在区域1或2
                            if(visited1||visited2)
                            {//先前已访问区域1或2，则记录路径
                                std::string rm(roadName);
                                if(passedRoads.empty()||passedRoads[passedRoads.size()-1]!=rm)
                                {//现在所处道路与上一条记录所在道路不是同一条，则加入容器passedRoads
                                    passedRoads.push_back(rm);
                                }
                            }
                        }

                    }
                    file.close();
                }
                //中间几天
                for(int x=requestStartDay+1;x<requestEndDay;++x)
                {
                    for(int y=0;y<=23;++y)
                    {
                        sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);//拼接文件名
                        std::ifstream file;
                        file.open(path,std::ios::in);
                        if (!file) {    //检查是否正常打开文件，无此记录则跳过
                                continue;
                            }
                        double longitude,latitude;
                        int day,hour,minute,second;
                        int travelTime;
                        while(std::getline(file,line))
                        {
                            //扫描文件每一行，得到经纬度、路名
                            sscanf(line.c_str(),"%d %d:%d:%d,%lf,%lf %s",&day,&hour,&minute,&second,&longitude,&latitude,roadName);
                            Coordinate currPos(longitude,latitude);//现在位置
                            Time currTime(day,hour,minute,second);//现在时刻
                            if(currPos.isInRectangle(ltPos1,rbPos1))
                            {//在区域1
                                visited1=true;//设置区域1已访问
                                if(visited2==true)
                                {//先前已访问过区域2
                                    visited2=false;//设置区域2未访问
                                    travelTime=timePassed(visitedTime,currTime);//通行时间
                                    if(travelTime<minTravelTime)
                                    {//更新 最小时间、最佳路径
                                        minTravelTime=travelTime;
                                        bestRoads=passedRoads;
                                        passedRoads.clear();
                                    }
                                }

                                //保证在本区域中最后一个点开始计时
                                visitedTime=currTime;

                            }
                            else if(currPos.isInRectangle(ltPos2,rbPos2))
                            {//在区域2
                                visited2=true;
                                if(visited1==true)
                                {
                                    visited1=false;
                                    travelTime=timePassed(visitedTime,currTime);//通行时间
                                    if(travelTime<minTravelTime)
                                    {//更新 最小时间、最佳路径
                                        minTravelTime=travelTime;
                                        bestRoads=passedRoads;
                                        passedRoads.clear();
                                    }
                                }

                                //保证在本区域中最后一个点开始计时
                                visitedTime=currTime;

                            }
                            else
                            {//不在区域1或2
                                if(visited1||visited2)
                                {//先前已访问区域1或2，则记录路径
                                    std::string rm(roadName);
                                    if(passedRoads.empty()||passedRoads[passedRoads.size()-1]!=rm)
                                    {//现在所处道路与上一条记录所在道路不是同一条，则加入容器passedRoads
                                        passedRoads.push_back(rm);
                                    }
                                }
                            }

                        }
                        file.close();
                    }
                }
                //最后一天
                for(int y=0;y<=requestEndHour;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);//拼接文件名
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件，无此记录则跳过
                            continue;
                        }
                    double longitude,latitude;
                    int day,hour,minute,second;
                    int travelTime;
                    while(std::getline(file,line))
                    {
                        //扫描文件每一行，得到经纬度、路名
                        sscanf(line.c_str(),"%d %d:%d:%d,%lf,%lf %s",&day,&hour,&minute,&second,&longitude,&latitude,roadName);
                        Coordinate currPos(longitude,latitude);//现在位置
                        Time currTime(day,hour,minute,second);//现在时刻
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {//在区域1
                            visited1=true;//设置区域1已访问
                            if(visited2==true)
                            {//先前已访问过区域2
                                visited2=false;//设置区域2未访问
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {//在区域2
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                travelTime=timePassed(visitedTime,currTime);//通行时间
                                if(travelTime<minTravelTime)
                                {//更新 最小时间、最佳路径
                                    minTravelTime=travelTime;
                                    bestRoads=passedRoads;
                                    passedRoads.clear();
                                }
                            }

                            //保证在本区域中最后一个点开始计时
                            visitedTime=currTime;

                        }
                        else
                        {//不在区域1或2
                            if(visited1||visited2)
                            {//先前已访问区域1或2，则记录路径
                                std::string rm(roadName);
                                if(passedRoads.empty()||passedRoads[passedRoads.size()-1]!=rm)
                                {//现在所处道路与上一条记录所在道路不是同一条，则加入容器passedRoads
                                    passedRoads.push_back(rm);
                                }
                            }
                        }

                    }
                    file.close();
                }
            }
            //build heap to select most frequently visited k(heapMaxSize) roads

        }
        std::string info="";//显示的信息
        if(minTravelTime==1e9)
        {
            info="此时间段无车辆来往这2个区域";
        }
        else
        {
            for(auto& i:bestRoads)
            {
                info+=i+'\n';
            }
            char timeInfo[40];
            sprintf(timeInfo,"\n此路径用时%d秒\n",minTravelTime);
            info+=timeInfo;
        }

        QMessageBox::information(this,"最快路径",info.c_str());
    });
}

MyWidget7::~MyWidget7()
{
    delete ui;
}
