#include <math.h>
#include "Arduino.h"
#include "Point.h"

Point::Point(const int &x, const int &y) {
    this->x = x;
    this->y = y;
}

float Point::distanceTo(const Point &p) const {
    // Serial.print("Sqrt of ");
    // Serial.println((p.x - x) + (p.y - y));
    return sqrt(square(p.x - x) + square(p.y - y));
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
