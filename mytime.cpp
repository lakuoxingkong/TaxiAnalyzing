#include "mytime.h"

Time::Time(int d,int h,int m,int s)
{
    day=d; hour=h; minute=m; second=s;
}


void Time::setTime(int d,int h,int m,int s)
{
    day=d; hour=h; minute=m; second=s;
}

int timePassed(Time& beg,Time& end)
{
    return end.second-beg.second+60*(end.minute-beg.minute)+3600*(end.hour-beg.hour)+86400*(end.day-beg.day);
}
