#include "Arduino.h"

#include <Adafruit_NeoPixel.h>
// #include <StandardCplusplus.h>
// #include <vector>

#include "macros/macros.h"
#include "src/geometry/Point.h"
#include "src/sensors/HC-SR04.h"
#include "src/lights/WS2811strip.h"
// #include "config.h"


HC_SR04 *sensors;
byte sensorCount = 0;
WS2811strip *lights;
byte lightCount = 0;

void setup() {
    Serial.begin(19200);
    Serial.println("setup start");

    // Point *points = new Point[1];

    Serial.println(freeRam());
    #include "config.h"
    // WS2811strip *s = new WS2811strip(Point(0, 0), TURN_POINTS(Point(100, 0), Point(100, 400)), 50, 7, NEO_GRB + NEO_KHZ400);

    Serial.println(freeRam());
    sensorCount = ARRAY_SIZE(hc_sr04);
    lightCount = ARRAY_SIZE(ws2811);
    sensors = hc_sr04[0];
    lights = ws2811[0];
    Serial.println("setup end");
}

void loop() {
    Serial.println("loop start");
    Point *points;
    for (byte i = 0; i < sensorCount; i++) {
        sensors[i].detect();
        points = sensors[i].getDetectedPoints();
        Serial.println(sensors[i].getDetectedPointsCount());
        Serial.print(points[0].x);
        Serial.print("x");
        Serial.print(points[0].y);
        Serial.println(" cm ");

        for (byte j = 0, size1 = sensorCount; j < size1; j++) {
        //     lights[j].reactToPoints(points, sensors[i].getDetectedPointsCount());
        }
    }
    Serial.println("loop end");
    delay(5000);
}
