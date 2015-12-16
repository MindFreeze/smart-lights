#ifndef SL_CLASS_HC_SR04
#define SL_CLASS_HC_SR04

#define MAX_DURATION_DIFF 20000

#include <math.h>
#include "Sensor.cpp"

class HC_SR04 : public Sensor
{
    public:
        HC_SR04(const Point &position, const Point &direction, int trigPin, int echoPin);
        virtual ~HC_SR04() {}
        Point getDetectedPoint();
        unsigned short measureDist();
    private:
        unsigned short prevDuration = 0;
        double rotationSin;
        double rotationCos;
        byte trig;
        byte echo;
};

HC_SR04::HC_SR04(const Point &position, const Point &direction, int trigPin, int echoPin) : Sensor(position) {
    Point vector = direction - position;
    double angle = atan2(vector.y, vector.x);
    rotationSin = sin(angle);
    rotationCos = cos(angle);
    trig = trigPin;
    echo = echoPin;
}

Point HC_SR04::getDetectedPoint() {
    unsigned short distance = measureDist();
    // rotate Point(distance, 0) around Point(0, 0) by the sensor's angle
    // and add sensor position
    return Point(rotationCos, distance) * distance + pos;
};

unsigned short HC_SR04::measureDist() {
    unsigned short duration;
    unsigned short distance;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    // Serial.print(duration);
    // Serial.print(" ms ");
    if (duration > prevDuration && duration - prevDuration > MAX_DURATION_DIFF) {
        distance = 0;
    } else {
        distance = duration / 58.77339916; // microseconds per cm * 2
    }
    prevDuration = duration;
    return distance; // cm
}

#endif
