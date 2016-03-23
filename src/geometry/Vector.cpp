#include <math.h>
#include "Vector.h"

Vector::Vector(const float &x, const float &y) {
    this->x = x;
    this->y = y;
}

Vector::Vector(const Point &p) {
    this->fromPoint(p);
}

Vector::Vector(const Point &from, const Point &to) {
    this->fromPoint(to - from);
}

/**
 * Vectors in the same direction but has unit length. http://math.stackexchange.com/a/175906
 */
void Vector::fromPoint(const Point &p) {
    float length = sqrt(square(p.x) + square(p.y));
    x = (p.x / length);
    y = (p.y / length);
}


Point Vector::findPoint(const Point &start, const word distance) {
    return (*this * distance) + start;
}

Point Vector::findPoint(const Point &start, const float distance) {
    return (*this * distance) + start;
}


Point Vector::operator *(const word &i) const
{
    return Point(round(x * i), round(y * i));
}

Point operator *(const word &i, const Vector &v)
{
    return v * i;
}

Point Vector::operator *(const float &i) const
{
    return Point(round(x * i), round(y * i));
}

Point operator *(const float &i, const Vector &v)
{
    return v * i;
}
