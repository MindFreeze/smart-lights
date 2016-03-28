#ifndef SL_CLASS_WS2811STRIP
#define SL_CLASS_WS2811STRIP

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "Light.h"

class WS2811strip : public Light
{
    public:
        WS2811strip(const Point &position, const byte &numKeyPoints, const Point keyPoints[], const word &numPixels, const byte &pin, const neoPixelType &flags);
        ~WS2811strip();
        void reactToPoints(const Point points[], const byte count);
        void printPixels();

    private:
        void calcPixelLocations(const byte &numKeyPoints, const Point keyPoints[]);
        byte distanceToLight(byte dist);
        Point *pixels;
        word pixelCount;
        Adafruit_NeoPixel strip;
        byte maxIntensity = 255;
        byte sensitivity = 20;
};

#endif
