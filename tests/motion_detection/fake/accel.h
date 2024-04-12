#ifndef _FAKE_ACCEL_H_
#define _FAKE_ACCEL_H_

#include <zephyr/drivers/sensor.h>
#include <stdbool.h>
#include "fake/stats.h"

extern struct fake_stats accel_fake_stats;

int accel_fake_sample_fetch(const struct device *dev,
			    enum sensor_channel chan);
int accel_fake_channel_get(const struct device *dev,
			   enum sensor_channel chan,
			   struct sensor_value *val);

void accel_fake_teardown(void);
void accel_fake_set_data(const struct sensor_value *data, size_t array_len);

#endif /* _FAKE_ACCEL_H_ */
