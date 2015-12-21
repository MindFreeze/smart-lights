#include <Adafruit_NeoPixel.h>

#include "macros/macros.h"
#include "src/Point.cpp"
#include "src/sensors/HC-SR04.cpp"
#include "src/lights/WS2811strip.cpp"
#include "config.h"

#define trigPin 13
#define echoPin 11

// Sensor a(Point(0, 0));

void setup() {
    Serial.begin (9600);

    FOREACH(byte, i, hc_sr04) {
        hc_sr04[i].setup();
    }
    FOREACH(byte, j, ws2811) {
        ws2811[j].setup();
    }

    // strip.begin();
    // strip.setPixelColor(2, 255, 0, 0); // GRB O.o
    // strip.show(); // Initialize all pixels to 'off'
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
