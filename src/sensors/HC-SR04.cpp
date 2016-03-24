#include "HC-SR04.h"

HC_SR04::HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin, word maxCmDistance) : Sensor(position), sonar(trigPin, echoPin, maxCmDistance) {
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

    if (distance > 0) {
        detectedPointsCount = 1;
        detectedPoints[0] = vector.findPoint(pos, distance);
    } else {
        detectedPointsCount = 0;
    }
};

word HC_SR04::measureDist() {
    word duration = sonar.ping_median();
    word distance;
    // Serial.print(duration);
    // Serial.print(" ms ");
    if (duration > prevDuration && duration - prevDuration > MAX_DURATION_DIFF) {
        distance = 0;
    } else {
        distance = sonar.convert_cm(duration);
        if (distance == maxDistance) {
            distance = 0;
        } else if (distance > maxDistance) {
            maxDistance = distance;
        }
    }
    prevDuration = duration;
    return distance; // cm
}
