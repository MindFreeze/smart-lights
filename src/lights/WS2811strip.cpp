#include "WS2811strip.h"
#include "../geometry/Vector.h"

WS2811strip::WS2811strip(const Point &position, const byte &numTurns, const Point *turnPoints, const word &numPixels, const byte &pin, const neoPixelType &flags) : Light(position) {
    // Serial.begin(19200);
    // Serial.println("cant reach this");
    pixelCount = numPixels;
    pixels = new Point[pixelCount];
    float length = 0;
    float pixelLength;
    const Point *prev = &pos;
    for (byte i = 0; i < numTurns; i++) {
        length += turnPoints[i].distanceTo(*prev);
        prev = &turnPoints[i];
    }
    // Serial.println(length);
    // Serial.println(pixelLength);
    pixelLength = length / pixelCount;

    float remaining = 0;
    Vector direction;
    byte pixNum = 0;
    prev = &pos;
    for (byte i = 0; i < numTurns; i++) {
        length = turnPoints[i].distanceTo(*prev); // current line length
        remaining = fmod(length, pixelLength);
        direction = Vector(*prev, turnPoints[i]);
        for (word j = 0; j < pixelCount; j++, pixNum++) {
            pixels[pixNum] = direction.findPoint(*prev, (float)(0.5 + j) * pixelLength - remaining);
        }
        // pixelPos = distance * vector + pos
        prev = &turnPoints[i];
    }

    strip = Adafruit_NeoPixel(pixelCount, pin, flags);
    strip.begin(); // Initialize all pixels to 'off'
    strip.show(); // send to strip

    for (byte i = 0; i < pixelCount; i++) {
        Serial.print(pixels[i].x);
        Serial.print("x");
        Serial.println(pixels[i].y);
    }
}

WS2811strip::~WS2811strip() {
    delete pixels;
}

void WS2811strip::reactToPoints(const Point *points, const byte count) {
    // strip.setPixelColor(2, 255, 0, 0); // GRB O.o
    word dist;
    byte minDist = 255;
    uint8_t light, targetLight;
    for (byte i = 0; i < pixelCount; i++) {
        for (byte j = 0; j < count; j++) {
            dist = pixels[i].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
        if (minDist < 255) {
            // light it up
            targetLight = distanceToLight(minDist);
            light = strip.getPixelColor(i);
            if (targetLight != light) {
                if (targetLight > light) {
                    light++;
                } else {
                    light--;
                }
                strip.setPixelColor(i, light, light, light);
            }
        }
    }
    strip.show(); // send to strip
}

byte WS2811strip::distanceToLight(byte dist) {
    // @TODO use a Gauss function here
    return 255 - dist;
}
