#ifndef ROAD_H
#define ROAD_H
#include<string>

class Road
{
public:
    std::string name;
    int passedTimes;
    Road(std::string n="",int p=0);

};

#endif // ROAD_H
