#include "map_macro.h"

#define NUMARGS(...)  (sizeof((int[]){0, ##__VA_ARGS__})/sizeof(int)-1)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define ARRAY_SIZE_P(x) (sizeof(*x) / sizeof((x)[0]))
#define FOREACH(indexType, index, array) for (indexType index = 0, size = ARRAY_SIZE(array); index < size; index++)
#define FOREACH_P(indexType, index, array) for (indexType index = 0, size = ARRAY_SIZE_P(array); index < size; index++)

#define TURN_POINTS(...) (sizeof((const Point[]){Point(0, 0), ##__VA_ARGS__})/sizeof(Point)-1), (Point*)(const Point[]){__VA_ARGS__}

// testing
#define PRINTLN(x) Serial.println(#x);
#define TST(...) MAP(PRINTLN, __VA_ARGS__);

// #define SL_ARRAY_OF_CLASS(type, ...) MAP(PRINTLN, __VA_ARGS__);

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
