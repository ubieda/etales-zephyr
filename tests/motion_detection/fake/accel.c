#define DT_DRV_COMPAT fake_accel

#include <zephyr/drivers/sensor.h>
#include "fake/accel.h"

struct fake_stats accel_fake_stats;

const struct sensor_value accel_fake_default[] = {
	{.val1 = 0,}, {.val1 = 0,}, {.val1 = 9,},
};

const struct sensor_value *accel_fake_values = accel_fake_default;
static size_t accel_fake_values_sizeof = ARRAY_SIZE(accel_fake_default);

static size_t counter;

int accel_fake_sample_fetch(const struct device *dev,
			    enum sensor_channel chan)
{
	fake_stats_update(&accel_fake_stats, accel_fake_sample_fetch);

	counter += 3;

	return 0;
}

int accel_fake_channel_get(const struct device *dev,
			   enum sensor_channel chan,
			   struct sensor_value *val)
{
	fake_stats_update(&accel_fake_stats, accel_fake_channel_get);

	val[0] = accel_fake_values[(counter - 3) % accel_fake_values_sizeof];
	val[1] = accel_fake_values[(counter -3 + 1) % accel_fake_values_sizeof];
	val[2] = accel_fake_values[(counter -3 + 2) % accel_fake_values_sizeof];

	return 0;
}

struct sensor_driver_api accel_fake_api = {
	.sample_fetch = accel_fake_sample_fetch,
	.channel_get = accel_fake_channel_get,
};

static int accel_fake_init(const struct device *dev)
{
	return 0;
}

void accel_fake_teardown(void)
{
	fake_stats_teardown(&accel_fake_stats);

	counter = 0;
	accel_fake_values = accel_fake_default;
	accel_fake_values_sizeof = ARRAY_SIZE(accel_fake_default);
}

void accel_fake_set_data(const struct sensor_value *data, size_t array_len)
{
	counter = 0;
	accel_fake_values = data;
	accel_fake_values_sizeof = array_len;
}

SENSOR_DEVICE_DT_INST_DEFINE(0, accel_fake_init, NULL,
			     NULL, NULL,
			     POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
			     &accel_fake_api);
