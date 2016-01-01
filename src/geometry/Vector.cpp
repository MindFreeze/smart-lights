#ifndef SL_CLASS_VECTOR
#define SL_CLASS_VECTOR

#include <math.h>
#include "Point.cpp"

class Vector
{
    public:
        Vector() {}
        Vector(const float &x, const float &y);
        Vector(const Point &p);
        Vector(const Point &from, const Point &to);
        ~Vector() {}
        Point findPoint(const Point &start, const word distance);
        Point findPoint(const Point &start, const float distance);
        float x = 0;
        float y = 0;
    private:
        void fromPoint(const Point &p);
};

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
    float length = sqrt((p.x * p.x) + (p.y * p.y));
    x = (p.x / length);
    y = (p.y / length);
}


Point operator*(const Vector &v, const word &i)
{
    return Point(round(v.x * i), round(v.y * i));
}

Point operator*(const word &i, const Vector &v)
{
    return v * i;
}

Point operator*(const Vector &v, const float &i)
{
    return Point(round(v.x * i), round(v.y * i));
}

Point operator*(const float &i, const Vector &v)
{
    return v * i;
}


Point Vector::findPoint(const Point &start, const word distance) {
    return distance * (*this) + start;
}

Point Vector::findPoint(const Point &start, const float distance) {
    return distance * (*this) + start;
}

#endif
