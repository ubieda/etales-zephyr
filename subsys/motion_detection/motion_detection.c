#include <zephyr/kernel.h>
#include <motion_detection.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

bool motion_detect_enabled;
motion_st_changed_t module_listener;

const struct device *accel_dev = DEVICE_DT_GET(DT_NODELABEL(motion_accel));

size_t motion_sample_ct;

static void motion_detection_thread_fn(void *v1, void *v2, void *v3)
{
	while (true) {
		if (motion_detect_enabled) {
			struct sensor_value accel_val[3] = {0};

			k_sleep(K_SECONDS(1));

			(void)sensor_sample_fetch(accel_dev);
			(void)sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_XYZ, accel_val);

			motion_sample_ct++;
			if (motion_sample_ct == 5) {
				module_listener(MOTION_ST_IDLE);
			}
		} else {
			k_sleep(K_FOREVER);
		}
	}
}

K_THREAD_DEFINE(motion_detection_thread_id, CONFIG_MOTION_DETECTION_THREAD_STACK_SIZE,
	motion_detection_thread_fn, NULL, NULL, NULL,
	CONFIG_MOTION_DETECTION_THREAD_PRIO, 0, 0);

int motion_detection_init(void)
{
	if (motion_detect_enabled) {
		return -EALREADY;
	}
	motion_detect_enabled = true;

	module_listener(MOTION_ST_UNKNOWN);

	k_thread_resume(motion_detection_thread_id);

	return 0;
}

bool motion_detection_is_enabled(void)
{
	return motion_detect_enabled;
}

void motion_detection_teardown(void)
{
	motion_detect_enabled = false;
	motion_sample_ct = 0;
}

int motion_detection_listener_add(motion_st_changed_t listener)
{
	module_listener = listener;

	return 0;
}
