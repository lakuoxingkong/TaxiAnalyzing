#include "mywidget1.h"
#include "ui_mywidget1.h"
//#include<QAxWidget>
#include<ActiveQt>
#include<string>
#include<stdio.h>
#include<fstream>
#include<QMessageBox>

MyWidget1::MyWidget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget1)
{
    ui->setupUi(this);

    ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    ui->axWidget->dynamicCall("Navigate(const QString&)","file:///D:/myTaxiData/myMap.html");//打开网页
    ui->axWidget->setProperty("Silent",true);//关闭脚本错误提示（不影响功能）
    QAxObject *document = ui->axWidget->querySubObject("Document");
    QAxObject *parentWindow = document->querySubObject("parentWindow");

    connect(ui->btn1,&QPushButton::clicked,[=](){
        bool isInt=true;//标示输入框内容是否整数
        int taxin=ui->lineEdit1->text().toInt(&isInt);
        if(!isInt)
        {
            QMessageBox::warning(this,"警告","输入的不是整数，请重新输入");
        }
        else
        {

            if(taxin<1||taxin>10357)
            {

                QMessageBox::warning(this,"警告","输入的数超出范围，请重新输入");
            }
            else//输入正常
            {
                parentWindow->dynamicCall("eval(QString,QString)","points.length=0;mass.clear();","JavaScript");//清空先前的标记点
                std::string taxiNum=ui->lineEdit1->text().toStdString();
                std::string path0="D:\\myTaxiData\\"+taxiNum;//为方便直接采用了绝对路径
                std::ifstream file;
                char path[100];
                for(int d=2;d<=8;++d)
                {
                    for(int h=0;h<=23;++h)
                    {
                        sprintf(path,"%s\\%02d%02d.txt",path0.c_str(),d,h);
                        file.open(path,std::ios::in);
                        if (!file) {    //检查文件是否存在（该时段是否有记录）
                                continue;
                            }
                        std::string line;
                        double longitude,latitude; int hour,minute,second,day;
                        while(std::getline(file,line))
                        {
                            sscanf(line.c_str(),"%d %d:%d:%d,%lf,%lf %*s",&day,&hour,&minute,&second,&longitude,&latitude);
                            char pushData[100];//保存JS代码
                            sprintf(pushData,"points.push({\"lnglat\":[%f,%f],\"time\":\"2008-02-%02d %02d:%02d:%02d\"});",longitude,latitude,day,hour,minute,second);
                            parentWindow->dynamicCall("eval(QString,QString)",pushData,"JavaScript");//向网页输入数据
                        }

                        file.close();
                    }
                }
                parentWindow->dynamicCall("eval(QString,QString)","func();","JavaScript");//作出标记点

            }
        }


    });
}

MyWidget1::~MyWidget1()
{
    delete ui;
}
