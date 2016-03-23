#ifndef SL_CLASS_HC_SR04
#define SL_CLASS_HC_SR04

#define MAX_DURATION_DIFF 20000

// #include <math.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Sensor.h"

class HC_SR04 : public Sensor
{
    public:
        HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin);
        ~HC_SR04();
        void detect();
        word measureDist();
    private:
        Vector vector;
        word prevDuration = 0;
        byte trig;
        byte echo;
};

#endif
