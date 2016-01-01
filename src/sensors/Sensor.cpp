#ifndef SL_CLASS_SENSOR
#define SL_CLASS_SENSOR

#include "../geometry/Point.cpp"
#include "../geometry/Vector.cpp"

class Sensor
{
    public:
        Sensor(const Point &position);
        virtual void getDetectedPoints(Point points[]) = 0;
        Point pos;
};

Sensor::Sensor(const Point &position) {
    pos = position;
}

#endif
