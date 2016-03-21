#ifndef SL_CLASS_LIGHT
#define SL_CLASS_LIGHT

#include "Arduino.h"
#include "../geometry/Point.h"

class Light
{
    public:
        Light(const Point &position);
        virtual void reactToPoints(const Point *points, const byte count) = 0;
        Point pos;
    private:
};

#endif
