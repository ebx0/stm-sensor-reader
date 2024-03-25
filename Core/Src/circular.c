#include "circular.h"

void buffer_init(buf_handle_t *p_handle) {
    p_handle->head = 0;
    p_handle->tail = 0;
    p_handle->size = 0;
    p_handle->capacity = MAX_BUFFER_SIZE;
}

uint8_t buffer_insert(buf_handle_t *p_handle, float value) {
    p_handle->buffer[p_handle->head] = value;
    p_handle->head = (p_handle->head + 1) % p_handle->capacity;
    p_handle->size++;
    return 0;
}

uint8_t buffer_extract(buf_handle_t *p_handle) {
    p_handle->tail = (p_handle->tail + 1) % p_handle->capacity;
    p_handle->size--;
    return 0;
}

uint8_t buffer_enter_value(buf_handle_t *p_handle, float value) {
    if (p_handle->size >= p_handle->capacity) {
        buffer_extract(p_handle);
    }
    buffer_insert(p_handle, value);
    return 0;
}

uint8_t buffer_get_value(buf_handle_t *p_handle, float *p_sensor_data) {
    if (p_handle == NULL || p_sensor_data == NULL)
        return -2;
    if (p_handle->size == 0)
        return -1;

    *p_sensor_data = p_handle->buffer[p_handle->tail];
    buffer_extract(p_handle);
    return 0;
}
