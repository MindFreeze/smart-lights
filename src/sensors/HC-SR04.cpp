#include "HC-SR04.h"

HC_SR04::HC_SR04(const Point &position, const Point &direction, const int &trigPin, const int &echoPin, word maxCmDistance) : Sensor(position), sonar(trigPin, echoPin, maxCmDistance) {
    vector = Vector(position, direction);
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
    word distance = sonar.convert_cm(duration);
    if (abs(distance - prevDistance) > MAX_DISTANCE_DIFF) {
        prevDistance = distance;
        distance = 0;
    } else {
        prevDistance = distance;
        if (distance > maxDistance - TOLERANCE) {
            maxDistance = distance;
            distance = 0;
        } else if (maxDistance > TOLERANCE && millis() & 1) {
            // constantly degrade maxDistance to avoid it getting stuck at a high false value
            maxDistance--;
        }
    }
    Serial.println(distance);
    return distance; // cm
}
