#ifndef SL_CLASS_SENSOR
#define SL_CLASS_SENSOR

#include "../Point.cpp"

class Sensor
{
    public:
        Sensor(const Point &position);
        virtual void setup();
        virtual Point getDetectedPoint() = 0;
        Point pos;
};

Sensor::Sensor(const Point &position) {
    pos = position;
}

#endif
