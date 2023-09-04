#ifndef TIME_H
#define TIME_H


class Time
{
public:
    int day;
    int hour;
    int minute;
    int second;
    Time(int d=0,int h=0,int m=0,int s=0);
    void setTime(int d=0,int h=0,int m=0,int s=0);
    friend int timePassed(Time& beg,Time& end);
};



#endif // TIME_H
