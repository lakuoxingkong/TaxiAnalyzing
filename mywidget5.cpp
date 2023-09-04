#include "mywidget5.h"
#include "ui_mywidget5.h"
#include"coordinate.h"
#include<stdio.h>
#include<fstream>
#include<string>
#include<QMessageBox>

MyWidget5::MyWidget5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget5)
{
    ui->setupUi(this);

    connect(ui->btn5,&QPushButton::clicked,[=]()
    {
        bool isInputCorrect[12];//标示输入框中内容是否正确
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
        int ans=0;
        std::string line;

        for(int taxiNum=1;taxiNum<=10357;++taxiNum)
        {
            printf("%d\n",taxiNum);
            bool visited1=false,visited2=false;//记录区域1,2之中哪个是最近访问的区域，初始设为两个都没访问
            char path[100],path0[100];
            sprintf(path0,"D:\\myTaxiData\\%d\\",taxiNum);
            if(requestStartDay==requestEndDay)
            {
                for(int y=requestStartHour;y<=requestEndHour;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查文件是否存在（该时段是否有记录）
                            continue;
                        }
                    double longitude,latitude;
                    while(std::getline(file,line))
                    {
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf",&longitude,&latitude);
                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {//在区域1
                            visited1=true;
                            if(visited2==true)
                            {//最近访问了区域2
                                visited2=false;
                                ++ans;
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {//在区域2
                            visited2=true;
                            if(visited1==true)
                            {//最近访问了区域1
                                visited1=false;
                                ++ans;
                            }
                        }

                    }
                    file.close();
                }
            }
            else
            {
                //第一天
                for(int y=requestStartHour;y<=23;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件
                            continue;
                        }
                    double longitude,latitude;
                    while(std::getline(file,line))
                    {
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf",&longitude,&latitude);
                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {
                            visited1=true;
                            if(visited2==true)
                            {
                                visited2=false;
                                ++ans;
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                ++ans;
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
                        sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                        std::ifstream file;
                        file.open(path,std::ios::in);
                        if (!file) {    //检查是否正常打开文件
                                continue;
                            }
                        double longitude,latitude;
                        while(std::getline(file,line))
                        {
                            sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf",&longitude,&latitude);
                            Coordinate currPos(longitude,latitude);
                            if(currPos.isInRectangle(ltPos1,rbPos1))
                            {
                                visited1=true;
                                if(visited2==true)
                                {
                                    visited2=false;
                                    ++ans;
                                }
                            }
                            else if(currPos.isInRectangle(ltPos2,rbPos2))
                            {
                                visited2=true;
                                if(visited1==true)
                                {
                                    visited1=false;
                                    ++ans;
                                }
                            }

                        }
                        file.close();
                    }
                }
                //最后一天
                for(int y=0;y<=requestEndHour;++y)
                {
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件
                            continue;
                        }
                    double longitude,latitude;
                    while(std::getline(file,line))
                    {
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf",&longitude,&latitude);
                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {
                            visited1=true;
                            if(visited2==true)
                            {
                                visited2=false;
                                ++ans;
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                ++ans;
                            }
                        }

                    }
                    file.close();
                }
            }
        }
        char info[20];
        printf("%d\n",ans);
        sprintf(info,"车流量：%d辆次",ans);
        QMessageBox::information(this,"出租车数量",info);


    });
}

MyWidget5::~MyWidget5()
{
    delete ui;
}
