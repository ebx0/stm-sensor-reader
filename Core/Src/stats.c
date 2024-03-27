#include "stats.h"

uint8_t stats_find(const float data[], uint8_t size, buf_stats_t *p_handle) {
	float min = data[0];
	float max = data[0];
	float sum = 0;

	for (int i = 0; i < size; i++) {
		if (data[i] < min)
			min = data[i];
		if (data[i] > max)
			max = data[i];
		sum += data[i];
	}
	float mean = sum / size;

	// Calculating sum of squared differences
	float sumSqDiff = 0;
	for (int i = 0; i < size; i++) {
		float diff = data[i] - mean; // Step 2
		sumSqDiff += diff * diff;    // Step 3-4
	}
	float variance = sumSqDiff / size; // Step 5
	float sd = sqrt(variance);         // Step 6

	float median = findMedian(data, size);

	p_handle->max = max;
	p_handle->min = min;
	p_handle->median = median;
	p_handle->sd = sd;
	return 0;
}


uint8_t stats_transmit(UART_HandleTypeDef *huart, buf_handle_t *p_handle){
	char tx_buffer[TX_BUFFER_SIZE]; // Buffer to hold formatted time string
	float data_array[CIRCULAR_BUFFER_SIZE] = {0};
	uint8_t data_size = 0;
	uint8_t buffer_data_size = p_handle->size;
	buf_stats_t stats;
	for(int i = 0; i < buffer_data_size; i++){
		buffer_get_value(p_handle, &data_array[i]);

		snprintf(tx_buffer, TX_BUFFER_SIZE, " (%.2f), size:%d\n", data_array[i], p_handle->size);
		HAL_UART_Transmit(huart, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY);

		data_size++;
	}
	stats_find(data_array, data_size, &stats);
	snprintf(tx_buffer, TX_BUFFER_SIZE, "Min: %.2f Max: %.2f Median: %.2f SD: %.2f \n", stats.min, stats.max, stats.median, stats.sd);
	HAL_UART_Transmit(huart, (uint8_t *)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY);

	return 0;
}
