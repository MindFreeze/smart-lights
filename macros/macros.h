#include "map_macro.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define FOREACH(indexType, index, array) for (indexType index = 0, size = ARRAY_SIZE(array); index < size; index++)

// testing
#define PRINTLN(x) Serial.println(#x);
#define TST(...) MAP(PRINTLN, __VA_ARGS__);

// #define SL_ARRAY_OF_CLASS(type, ...) MAP(PRINTLN, __VA_ARGS__);
