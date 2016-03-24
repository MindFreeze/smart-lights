#ifndef SL_CLASS_HC_SR04
#define SL_CLASS_HC_SR04

#define MAX_DURATION_DIFF 20000
#define MAX_DISTANCE 4000

#include <Arduino.h>
#include <NewPing.h>
#include "Sensor.h"

class HC_SR04 : public Sensor
{
    public:
        HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin, word maxCmDistance = MAX_DISTANCE);
        ~HC_SR04();
        void detect();
        word measureDist();

    private:
        NewPing sonar;
        byte trig;
        byte echo;
        Vector vector;
        word maxDistance = 0;
        word prevDuration = 0;
};

#endif
