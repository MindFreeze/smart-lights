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
    // strip.show(); // send to strip
}

WS2811strip::~WS2811strip() {
    delete [] pixels;
}

void WS2811strip::reactToPoints(const Point *points, const byte count) {
    // strip.setPixelColor(2, 255, 0, 0); // GRB O.o
    word dist;
    byte minDist;
    uint8_t light, targetLight;
    for (byte i = 0; i < pixelCount; i++) {
        minDist = 100;
        for (byte j = 0; j < count; j++) {
            dist = pixels[i].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
            }
            // if (i >= 49) {
            //     Serial.print("Pixel ");
            //     Serial.print(pixels[i].x);
            //     Serial.print("x");
            //     Serial.print(pixels[i].y);
            //     Serial.print(" Point ");
            //     Serial.print(points[j].x);
            //     Serial.print("x");
            //     Serial.print(points[j].y);
            //     Serial.print(" dist ");
            //     Serial.print(dist);
            //     Serial.print(" minDist ");
            //     Serial.println(minDist);
            // }
        }
        // if (minDist < 255) {
            // light it up
            targetLight = distanceToLight(minDist);
            light = strip.getPixelColor(i);
            if (targetLight != light) {
                if (targetLight < light) {
                    // light += (targetLight - light) / 40;
                    // if (light < 40 && light > 0 && targetLight == 0) {
                    //     light--;
                    // }
                    light--;
                } else if (light < targetLight) {
                    // light += (targetLight - light) / 20;
                    light++;
                }
                // if (i >= 49) {
                //     Serial.print("distance ");
                //     Serial.print(minDist);
                //     Serial.print(" light ");
                //     Serial.println(targetLight);
                // }
                // Serial.print(i);
                // Serial.print(" to ");
                // Serial.println(light);
                strip.setPixelColor(i, light, light, light);
            }
        // }
    }
    strip.show(); // send to strip
}

byte WS2811strip::distanceToLight(byte dist) {
    // @TODO use a Gauss function here
    return 100 - dist;
    // if (dist < 10) {
    //     return 100;
    // }
    // return 0;
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
    // Serial.println("length");
    // Serial.println(length);
    // Serial.println(pixelLength);

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
        // pixelPos = distance * vector + pos
        prev = &keyPoints[i];
    }
}
