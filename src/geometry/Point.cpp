#ifndef SL_CLASS_POINT
#define SL_CLASS_POINT

#include <math.h>

class Point
{
    public:
        Point() {}
        Point(const int &x, const int &y);
        ~Point() {}
        float distanceTo(const Point &p) const;
        Point& operator=(const Point &p);
        int x = 0;
        int y = 0;
};

Point::Point(const int &x, const int &y) {
    this->x = x;
    this->y = y;
}

float Point::distanceTo(const Point &p) const {
    return sqrt((p.x - x) + (p.y - y));
}


Point& Point::operator=(const Point &p)
{
    x = p.x;
    y = p.y;
    return *this;
}

Point operator+(const Point &p1, const Point &p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point &p1, const Point &p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator*(const Point &p, const int &i)
{
    return Point(p.x * i, p.y * i);
}

Point operator*(const int &i, const Point &p)
{
    return p * i;
}

#endif
