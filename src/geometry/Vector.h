#ifndef SL_CLASS_VECTOR
#define SL_CLASS_VECTOR

#include "Arduino.h"
#include "Point.h"

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

        Point operator*(const word &i) const;
        Point operator*(const float &i) const;

    private:
        void fromPoint(const Point &p);
};

#endif
