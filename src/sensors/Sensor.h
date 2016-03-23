#ifndef SL_CLASS_SENSOR
#define SL_CLASS_SENSOR

#include "../geometry/Point.h"
#include "../geometry/Vector.h"

class Sensor
{
    public:
        Sensor(const Point &position) {
            pos = position;
        };
        virtual void detect() = 0;
        Point *getDetectedPoints() {
            return detectedPoints;
        };
        byte getDetectedPointsCount() {
            return detectedPointsCount;
        };
        Point pos;

    protected:
        Point *detectedPoints = 0;
        byte detectedPointsCount = 0;
};

#endif
