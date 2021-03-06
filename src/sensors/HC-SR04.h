#ifndef SL_CLASS_HC_SR04
#define SL_CLASS_HC_SR04

#define MAX_DISTANCE 4000
#define MAX_DISTANCE_DIFF 10
#define TOLERANCE 10

#include <Arduino.h>
#include <NewPing.h>
#include <math.h>
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
        Vector vector;
        word maxDistance = TOLERANCE; // will auto grow
        word prevDistance = 0;
};

#endif
