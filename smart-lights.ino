#include "Arduino.h"

#include <Adafruit_NeoPixel.h>
// #include <StandardCplusplus.h>
// #include <vector>

#include "macros/macros.h"
#include "src/geometry/Point.h"
#include "src/sensors/HC-SR04.h"
#include "src/lights/WS2811strip.h"
// #include "src/geometry/PointList.h"

#include "config.h"

byte sensorCount = ARRAY_SIZE(sensors);
byte lightCount = ARRAY_SIZE(lights);

void setup() {
    Serial.begin(19200);
    Serial.println("setup start");

    // Point *points = new Point[1];

    // Serial.println(freeRam());
    // #include "config.h"

    Serial.println(freeRam());
    // ((WS2811strip*)lights[0])->printPixels();
    Serial.println("setup end");
}

void loop() {
    // Serial.println("loop start");
    Point points[MAX_OBJECTS];
    byte count = 0, currentCount;
    Point *p;
    for (byte i = 0; i < sensorCount; i++) {
        sensors[i]->detect();
        p = sensors[i]->getDetectedPoints();
        currentCount = sensors[i]->getDetectedPointsCount();
        for (byte k = 0; k < currentCount && count < MAX_OBJECTS; k++, count++) {
            points[count] = p[k];
        }
        // Serial.println(sensors[i]->getDetectedPointsCount());
        // Serial.print(points[0].x);
        // Serial.print("x");
        // Serial.print(points[0].y);
        // Serial.println(" cm ");
    }

    for (byte j = 0; j < lightCount; j++) {
        lights[j]->reactToPoints(points, count);
        // delay(2000);
    }
    // Serial.println("loop end");
    // delay(600);
}
