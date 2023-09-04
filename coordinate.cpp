#include "coordinate.h"

Coordinate::Coordinate(double a,double b)
{
    this->longitude=a; this->latitude=b;
}

bool Coordinate::isInRectangle(Coordinate lt,Coordinate rb)
{
    if(this->longitude>lt.longitude && this->longitude<rb.longitude && this->latitude<lt.latitude &&this->latitude>rb.latitude)
    {
        return true;
    }
    return false;
}
