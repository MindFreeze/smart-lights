#include "WS2811strip.h"
#include "../geometry/Vector.h"

WS2811strip::WS2811strip(const Point &position, const byte &numKeyPoints, const Point keyPoints[], const word &numPixels, const byte &pin, const neoPixelType &flags) : Light(position) {
    // Serial.begin(19200);
    // Serial.println("cant reach this");
    pixelCount = numPixels;
    pixels = new Point[pixelCount];

    calcPixelLocations(numKeyPoints, keyPoints);

    strip = Adafruit_NeoPixel(pixelCount, pin, flags);
    strip.begin(); // Initialize all pixels to 'off'
}

WS2811strip::~WS2811strip() {
    delete [] pixels;
}

void WS2811strip::reactToPoints(const Point *points, const byte count) {
    // strip.setPixelColor(2, 255, 0, 0); // GRB O.o
    word dist;
    byte minDist;
    uint8_t light, targetLight;
    short diff;
    for (byte i = 0; i < pixelCount; i++) {
        minDist = 255;
        for (byte j = 0; j < count; j++) {
            dist = pixels[i].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
        // light it up
        targetLight = distanceToLight(minDist);
        light = strip.getPixelColor(i);
        if (targetLight != light) {
            diff = abs(targetLight - light);
            if (targetLight < light) {
                light -= diff / 64 + 1;
            } else if (light < targetLight) {
                light += diff / 127 + 1;
            }
            strip.setPixelColor(i, light, light, light);
        }
    }
    strip.show(); // send to strip
}


/**
 * Use a Gaussian function to convert distance to light intensity
 * @param  dist Distance from light source
 * @return      Light intensity
 */
byte WS2811strip::distanceToLight(byte dist) {
    return maxIntensity * exp(-1 * (square(dist) / (2 * square(sensitivity))));
}

void WS2811strip::printPixels() {
    // Point keyPoints[] = {Point(100, 0), Point(100, 400)};
    // calcPixelLocations(sizeof(keyPoints) / sizeof(Point), keyPoints);
    for (byte i = 0; i < pixelCount; i++) {
        Serial.print(pixels[i].x);
        Serial.print("x");
        Serial.println(pixels[i].y);
    }
}

void WS2811strip::calcPixelLocations(const byte &numKeyPoints, const Point keyPoints[]) {
    Serial.println("calcPixelLocations");
    float length = 0;
    const Point *prev = &pos;
    for (byte i = 0; i < numKeyPoints; i++) {
        length += keyPoints[i].distanceTo(*prev);
        prev = &keyPoints[i];
    }
    float pixelLength = length / pixelCount;

    float remaining = 0;
    Vector direction;
    prev = &pos;
    word pixNum = 0;
    word pixCountForLine;
    for (byte i = 0; i < numKeyPoints; i++) {
        length = keyPoints[i].distanceTo(*prev); // current line length
        pixCountForLine = floor(length / pixelLength);
        remaining = length - (pixCountForLine * pixelLength);
        direction = Vector(*prev, keyPoints[i]);
        // Serial.print("Vector ");
        // Serial.print(direction.x);
        // Serial.print("x");
        // Serial.println(direction.y);
        for (word j = 0; j < pixCountForLine; j++, pixNum++) {
            pixels[pixNum] = direction.findPoint(*prev, (float)(0.5 + j) * pixelLength - remaining);
            // Serial.print("Pixel ");
            // Serial.print(pixels[pixNum].x);
            // Serial.print("x");
            // Serial.println(pixels[pixNum].y);
        }
        prev = &keyPoints[i];
    }
}
