#ifndef SL_CLASS_WS2811STRIP
#define SL_CLASS_WS2811STRIP

#include <math.h>
#include "Light.cpp"

class WS2811strip : public Light
{
    public:
        WS2811strip(const Point &position, const word &numTurns, const Point turnPoints[], const word &pixelCount, const byte &pin, const neoPixelType &flags);
        ~WS2811strip();
        void reactToPoints(const Point points[]);
    private:
        Point *pixels;
        Adafruit_NeoPixel strip;
        byte distanceToLight(byte dist);
};

WS2811strip::WS2811strip(const Point &position, const word &numTurns, const Point turnPoints[], const word &pixelCount, const byte &pin, const neoPixelType &flags) : Light(position) {
    Serial.println("cant reach this");
    pixels = new Point[pixelCount];
    float length = 0;
    float pixelLength;
    const Point *prev = &pos;
    FOREACH(byte, i, turnPoints) {
        length += turnPoints[i].distanceTo(*prev);
        prev = &turnPoints[i];
    }
    // Serial.println(length);
    // Serial.println(pixelLength);
    pixelLength = length / pixelCount;

    word countForLine;
    float remaining = 0;
    Vector direction;
    byte pixNum = 0;
    prev = &pos;
    FOREACH(byte, i, turnPoints) {
        length = turnPoints[i].distanceTo(*prev); // current line length
        countForLine = length / pixelLength;
        remaining = fmod(length, pixelLength);
        direction = Vector(*prev, turnPoints[i]);
        for (int j = 0; j < pixelCount; j++, pixNum++) {
            pixels[pixNum] = direction.findPoint(*prev, (float)(0.5 + j) * pixelLength - remaining);
        }
        // pixelPos = distance * vector + pos
        prev = &turnPoints[i];
    }

    strip = Adafruit_NeoPixel(pixelCount, pin, flags);
    strip.begin(); // Initialize all pixels to 'off'
    strip.show(); // send to strip

    // Serial.println(ARRAY_SIZE_P(pixels)); // =0 O.o
    FOREACH_P(byte, i, pixels) {
        Serial.print(pixels[i].x);
        Serial.print("x");
        Serial.println(pixels[i].y);
    }
}

WS2811strip::~WS2811strip() {
    delete pixels;
}

void WS2811strip::reactToPoints(const Point points[]) {
    // strip.setPixelColor(2, 255, 0, 0); // GRB O.o
    // strip.show(); // Initialize all pixels to 'off'
    word dist;
    byte minDist = 255;
    uint8_t light, targetLight;
    FOREACH_P(byte, i, pixels) {
        FOREACH_P(byte, j, points) {
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

#endif
