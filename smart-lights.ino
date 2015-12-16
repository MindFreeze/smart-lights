#include "headers/macros.h"
#include "src/Point.cpp"
#include "src/Sensor.cpp"
#include "src/HC-SR04.cpp"
#include "config.h"

#define trigPin 13
#define echoPin 11

// Sensor a(Point(0, 0));

void setup() {
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    // int distance = hc_sr04[0].measureDist();
    Point p = hc_sr04[0].getDetectedPoint();
    Serial.print(p.x);
    Serial.print("x");
    Serial.print(p.y);
    Serial.println(" cm ");
    delay(500);
}
