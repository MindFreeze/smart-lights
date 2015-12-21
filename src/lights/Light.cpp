#ifndef SL_CLASS_LIGHT
#define SL_CLASS_LIGHT

#include "../Point.cpp"

class Light
{
    public:
        Light(const Point &position);
        virtual void reactToPoints(const Point points[]);
        virtual void setup();
        Point pos;
    private:
};

Light::Light(const Point &position) {
    pos = position;
}

#endif
