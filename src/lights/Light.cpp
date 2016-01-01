#ifndef SL_CLASS_LIGHT
#define SL_CLASS_LIGHT

#include "../geometry/Point.cpp"

class Light
{
    public:
        Light(const Point &position);
        virtual ~Light() = 0;
        virtual void reactToPoints(const Point points[]);
        Point pos;
    private:
};

Light::Light(const Point &position) {
    Serial.println(333);
    pos = position;
}

#endif
