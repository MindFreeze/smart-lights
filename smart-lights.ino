#include <Adafruit_NeoPixel.h>

// #include <StandardCplusplus.h>
// #include <vector>

#include "macros/macros.h"
#include "src/geometry/Point.cpp"
#include "src/sensors/HC-SR04.cpp"
#include "src/lights/WS2811strip.cpp"
// #include "config.h"


HC_SR04 *sensors;
WS2811strip *lights;

void setup() {
    Serial.begin(9600);
    Serial.println("setup start");

    // Point *points = new Point[1];

    // Serial.println(freeRam());
    #include "config.h"

    Serial.println(freeRam());
    sensors = hc_sr04;
    lights = ws2811;
    Serial.println("setup end");
}

void loop() {
    Serial.println("loop start");
    // Serial.println(ARRAY_SIZE_P(sensors));
    Point *points;
    for (byte i = 0, size = ARRAY_SIZE_P(sensors); i < size; i++) {
        sensors[i].getDetectedPoints(points);
        Serial.print(points[0].x);
        Serial.print("x");
        Serial.print(points[0].y);
        Serial.println(" cm ");

        // Serial.println(ARRAY_SIZE_P(lights));
        for (byte j = 0, size1 = ARRAY_SIZE_P(sensors); j < size1; j++) {
            lights[j].reactToPoints(points);
        }
        delete [] points;
    }
    Serial.println("loop end");
    delay(5000);
}
