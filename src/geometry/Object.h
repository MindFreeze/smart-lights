#ifndef SL_CLASS_OBJECT
#define SL_CLASS_OBJECT

#include "Arduino.h"
#include "Point.h"

class Object
{
    public:
        Object(const Point &pos, const word &source);
        ~Object() {}
        Point position;
        word source;
};

#endif
