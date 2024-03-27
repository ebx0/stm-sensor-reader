#ifndef STATS_H
#define STATS_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "filter.h"

#define TX_BUFFER_SIZE 127

typedef struct {
    float min;
    float max;
    float median;
    float sd;
} buf_stats_t;

uint8_t stats_find(const float data[], uint8_t, buf_stats_t*);
uint8_t stats_transmit(UART_HandleTypeDef*, buf_handle_t*);

#endif /* STATS_H */
