#ifndef FILTER_H
#define FILTER_H

#define MOV_WINDOW_SIZE 6

#include <stdint.h>
#include <stddef.h>
#include <math.h>

#include "circular.h"

int compareFloats(const void *a, const void *b);
float findMedian(float array[], uint8_t);
float filter_sensor_value(buf_handle_t*, float);

#endif /* FILTER_H */
