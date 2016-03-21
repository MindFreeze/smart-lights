#include <math.h>
#include "Point.h"

Point::Point(const int &x, const int &y) {
    this->x = x;
    this->y = y;
}

float Point::distanceTo(const Point &p) const {
    return sqrt((p.x - x) + (p.y - y));
}


Point& Point::operator =(const Point &p)
{
    x = p.x;
    y = p.y;
    return *this;
}

Point Point::operator +(const Point &p2) const
{
    return Point(x + p2.x, y + p2.y);
}

Point Point::operator -(const Point &p2) const
{
    return Point(x - p2.x, y - p2.y);
}

Point Point::operator *(const int &i) const
{
    return Point(x * i, y * i);
}

Point operator *(const int &i, const Point &p)
{
    return p * i;
}
