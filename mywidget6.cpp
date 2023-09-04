#include "mywidget6.h"
#include "ui_mywidget6.h"
#include"coordinate.h"
#include"road.h"
#include<stdio.h>
#include<fstream>
#include<string>
#include<QMessageBox>
#include<vector>
#include<unordered_map>
#include<queue>

struct cmp
{
    bool operator()(const Road& a,const Road& b)
    {
        return a.passedTimes>b.passedTimes;
    }
};

void addToTable(std::vector<std::string>& vec,std::unordered_map<std::string,int>& hashmap)
{
    for(auto &i:vec)
    {//遍历途径的路段
        if(hashmap.find(i)!=hashmap.end())
        {//哈希表中已有记录
            ++hashmap[i];
        }
        else
        {
            hashmap[i]=1;
        }
    }
    vec.clear();//清空途径路段
}


MyWidget6::MyWidget6(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget6)
{
    ui->setupUi(this);

    connect(ui->btn6,&QPushButton::clicked,[=]()
    {

        bool isInputCorrect[13];//标示输入框中内容是否正确
        std::unordered_map<std::string,int> roadPassingTimes;//哈希表，记录各路段途径的次数

        int heapMaxSize=ui->lineEdit6->text().toInt(isInputCorrect);//最后显示的频繁道路数量k
        std::priority_queue<Road,std::vector<Road>,cmp> heap;//小顶堆，得到前heapMaxSize个最频繁路段

        Coordinate ltPos1(ui->lineEdit2->text().toDouble(isInputCorrect+1),ui->lineEdit3->text().toDouble(isInputCorrect+2));//矩形区域1左上、右下坐标
        Coordinate rbPos1(ui->lineEdit2_2->text().toDouble(isInputCorrect+3),ui->lineEdit3_2->text().toDouble(isInputCorrect+4));
        Coordinate ltPos2(ui->lineEdit2_3->text().toDouble(isInputCorrect+5),ui->lineEdit3_3->text().toDouble(isInputCorrect+6));//矩形区域2左上、右下坐标
        Coordinate rbPos2(ui->lineEdit2_4->text().toDouble(isInputCorrect+7),ui->lineEdit3_4->text().toDouble(isInputCorrect+8));
        int requestStartDay=ui->lineEdit4_1->text().toInt(isInputCorrect+9),requestStartHour=ui->lineEdit4_2->text().toInt(isInputCorrect+10);//查询的开始日、时
        int requestEndDay=ui->lineEdit4_3->text().toInt(isInputCorrect+11),requestEndHour=ui->lineEdit4_4->text().toInt(isInputCorrect+12);//查询的结束日、时
        for(int i=0;i<13;++i)
        {
            if(!isInputCorrect[i])
            {
                QMessageBox::warning(this,"警告","非法输入");
                return;
            }
        }
        //输入正确
        int ans=0;
        char roadName[40];
        std::string line;

        for(int taxiNum=1;taxiNum<=1000;++taxiNum)
        {
            std::vector<std::string> passedRoads;//记录本车本次路径中途径的路段
            bool visited1=false,visited2=false;
            //格式："D:\\Qt\\Projects\\Learn0219\\taxi_log_2008_by_id\\"+车号+"\\"+日时.txt
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
                    while(std::getline(file,line))
                    {
                        //扫描文件每一行，得到经纬度、路名
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf %s",&longitude,&latitude,roadName);


                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {//在区域1
                            visited1=true;
                            if(visited2==true)
                            {//先前已访问过区域2
                                visited2=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);//把途经道路放入哈希表roadPassingTimes，并清除passedRoads
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);
                            }
                        }
                        else
                        {//两区域都不在
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
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf %s",&longitude,&latitude,roadName);

                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {
                            visited1=true;
                            if(visited2==true)
                            {
                                visited2=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);
                            }
                        }
                        else
                        {//两区域都不在
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
                        sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                        std::ifstream file;
                        file.open(path,std::ios::in);
                        if (!file) {    //检查是否正常打开文件
                                continue;
                            }
                        double longitude,latitude;
                        while(std::getline(file,line))
                        {
                            sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf %s",&longitude,&latitude,roadName);

                            Coordinate currPos(longitude,latitude);
                            if(currPos.isInRectangle(ltPos1,rbPos1))
                            {
                                visited1=true;
                                if(visited2==true)
                                {
                                    visited2=false;
                                    ++ans;
                                    addToTable(passedRoads,roadPassingTimes);
                                }
                            }
                            else if(currPos.isInRectangle(ltPos2,rbPos2))
                            {
                                visited2=true;
                                if(visited1==true)
                                {
                                    visited1=false;
                                    ++ans;
                                    addToTable(passedRoads,roadPassingTimes);
                                }
                            }
                            else
                            {//两区域都不在
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
                    sprintf(path,"%s%02d%02d.txt",path0,requestStartDay,y);
                    std::ifstream file;
                    file.open(path,std::ios::in);
                    if (!file) {    //检查是否正常打开文件
                            continue;
                        }
                    double longitude,latitude;
                    while(std::getline(file,line))
                    {
                        sscanf(line.c_str(),"%*d %*d:%*d:%*d,%lf,%lf %s",&longitude,&latitude,roadName);

                        Coordinate currPos(longitude,latitude);
                        if(currPos.isInRectangle(ltPos1,rbPos1))
                        {
                            visited1=true;
                            if(visited2==true)
                            {
                                visited2=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);
                            }
                        }
                        else if(currPos.isInRectangle(ltPos2,rbPos2))
                        {
                            visited2=true;
                            if(visited1==true)
                            {
                                visited1=false;
                                ++ans;
                                addToTable(passedRoads,roadPassingTimes);
                            }
                        }
                        else
                        {//两区域都不在
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
        printf("%d\n",ans);
        for(auto &i:roadPassingTimes)
        {
            if(heap.size()<heapMaxSize)
            {
                heap.push(Road(i.first,i.second));
            }
            else if(roadPassingTimes[heap.top().name]<i.second)
            {
                heap.pop();
                heap.push(Road(i.first,i.second));
            }
        }
        std::string info;
        while(!heap.empty())
        {
            info+=heap.top().name+'\n';
            heap.pop();
        }
        char title[20];
        sprintf(title,"最频繁的%d条路",heapMaxSize);
        QMessageBox::information(this,title,info.c_str());


    });
}



MyWidget6::~MyWidget6()
{
    delete ui;
}
