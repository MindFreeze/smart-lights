#ifndef SL_CLASS_HC_SR04
#define SL_CLASS_HC_SR04

#define MAX_DURATION_DIFF 20000

#include <math.h>
#include "Sensor.cpp"
#include "../Point.cpp"
#include "../Vector.cpp"

class HC_SR04 : public Sensor
{
    public:
        HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin);
        ~HC_SR04() {}
        void setup();
        Point getDetectedPoint();
        word measureDist();
    private:
        Vector vector;
        word prevDuration = 0;
        byte trig;
        byte echo;
};

HC_SR04::HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin) : Sensor(position) {
    vector = Vector(position, direction);
    double angle = atan2(vector.y, vector.x);
    trig = trigPin;
    echo = echoPin;
}

void HC_SR04::setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

Point HC_SR04::getDetectedPoint() {
    word distance = measureDist();
    // rotate Point(distance, 0) around Point(0, 0) by the sensor's angle
    // and add sensor position
    // return Point(rotationCos, distance) * distance + pos;

    return distance * vector + pos;
};

word HC_SR04::measureDist() {
    word duration;
    word distance;
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
