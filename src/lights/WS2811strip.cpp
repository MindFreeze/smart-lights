#ifndef SL_CLASS_WS2811STRIP
#define SL_CLASS_WS2811STRIP

#include <math.h>
#include "Light.cpp"

class WS2811strip : public Light
{
    public:
        WS2811strip(const Point &position, const Point turnPoints[], const byte &pixelCount, const byte &pin, const neoPixelType &flags);
        virtual ~WS2811strip() {}
        void setup();
        void reactToPoints(const Point points[]);
    private:
        Point pixels[];
        Adafruit_NeoPixel strip;
};

WS2811strip::WS2811strip(const Point &position, const Point turnPoints[], const byte &pixelCount, const byte &pin, const neoPixelType &flags) : Light(position) {
    float length = 0;
    word pixelLength;
    const Point *prev = &pos;
    FOREACH(byte, i, turnPoints) {
        length += turnPoints[i].distanceTo(*prev);
        prev = &turnPoints[i];
    }
    Serial.println(length);
    pixelLength = length / pixelCount * 10; // mm

    strip = Adafruit_NeoPixel(pixelCount, pin, flags);
}

void WS2811strip::setup() {
    strip.begin(); // Initialize all pixels to 'off'
    strip.show(); // send to strip
}

void WS2811strip::reactToPoints(const Point points[]) {
}

#endif
