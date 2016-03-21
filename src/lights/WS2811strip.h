#ifndef SL_CLASS_WS2811STRIP
#define SL_CLASS_WS2811STRIP

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include "Light.h"

class WS2811strip : public Light
{
    public:
        WS2811strip(const Point &position, const byte &numTurns, const Point *turnPoints, const word &numPixels, const byte &pin, const neoPixelType &flags);
        ~WS2811strip();
        void reactToPoints(const Point *points, const byte count);
    private:
        Point *pixels;
        word pixelCount;
        Adafruit_NeoPixel strip;
        byte distanceToLight(byte dist);
};

#endif
