#include "map_macro.h"

// testing
#define PRINTLN(x) Serial.println(#x);
#define TST(...) MAP(PRINTLN, __VA_ARGS__);

#define SL_ARRAY_OF_CLASS(type, ...) MAP(PRINTLN, __VA_ARGS__);
