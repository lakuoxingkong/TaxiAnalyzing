#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
    Coordinate(double a=0,double b=0);
    double longitude;
    double latitude;
    bool isInRectangle(Coordinate lt,Coordinate rb);
};

#endif // COORDINATE_H
