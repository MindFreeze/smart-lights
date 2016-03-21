#ifndef SL_CLASS_POINT
#define SL_CLASS_POINT

class Point
{
    public:
        Point() {}
        Point(const int &x, const int &y);
        ~Point() {}
        float distanceTo(const Point &p) const;
        int x = 0;
        int y = 0;

        Point& operator =(const Point &p);
        Point operator +(const Point &p2) const;
        Point operator -(const Point &p2) const;
        Point operator *(const int &i) const;
};

#endif
