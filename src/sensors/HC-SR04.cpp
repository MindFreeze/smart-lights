#define MAX_DURATION_DIFF 20000

#include "HC-SR04.h"

HC_SR04::HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin) : Sensor(position) {
    vector = Vector(position, direction);
    // double angle = atan2(vector.y, vector.x);
    trig = trigPin;
    echo = echoPin;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    detectedPoints = new Point[1];
}

HC_SR04::~HC_SR04() {
    delete [] detectedPoints;
}

void HC_SR04::detect() {
    word distance = measureDist();
    // rotate Point(distance, 0) around Point(0, 0) by the sensor's angle
    // and add sensor position
    // return Point(rotationCos, distance) * distance + pos;

    if (distance > 0) {
        detectedPointsCount = 1;
        detectedPoints[0] = vector.findPoint(pos, distance);
    } else {
        detectedPointsCount = 0;
    }
};

word HC_SR04::measureDist() {
    // return 15;
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
