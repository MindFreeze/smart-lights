#ifndef SL_CLASS_LIGHT
#define SL_CLASS_LIGHT

#include "../Point.cpp"

class Light
{
    public:
        Light(const Point &position);
        virtual ~Light() {}
        Point pos;
};

Light::Light(const Point &position) {
    pos = position;
}

#endif
