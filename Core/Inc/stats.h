#ifndef STATS_H
#define STATS_H

#include <stdint.h>
#include <stddef.h>
#include <math.h>

typedef struct {
    float min;
    float max;
    float mean;
    float sd;
} buf_stats_t;

uint8_t stats_find(const float data[], int size, buf_stats_t* p_handle);

#endif /* STATS_H */
