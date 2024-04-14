#include <zephyr/kernel.h>
#include <motion_detection.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

bool motion_detect_enabled;
motion_st_changed_t module_listener;

const struct device *accel_dev = DEVICE_DT_GET(DT_NODELABEL(motion_accel));

#define ACCEL_AXIS_NUMBER 3

struct sensor_value accel_history[5][3];
size_t motion_sample_ct;

bool is_motion_detected(void)
{
	if (motion_sample_ct < 2) {
		return false;
	}

	for (size_t i = 0 ; i < 3 ; i++) {
		if (abs(accel_history[(motion_sample_ct - 1)][i].val1
			- accel_history[motion_sample_ct - 2][i].val1) >= 2) {
			return true;
		}
	}

	return false;
}

static void motion_detection_thread_fn(void *v1, void *v2, void *v3)
{
	while (true) {
		if (motion_detect_enabled) {
			struct sensor_value accel_val[3] = {0};

			k_sleep(K_SECONDS(1));

			(void)sensor_sample_fetch(accel_dev);
			(void)sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_XYZ, accel_val);

			accel_history[motion_sample_ct % 5][0] = accel_val[0];
			accel_history[motion_sample_ct % 5][1] = accel_val[1];
			accel_history[motion_sample_ct % 5][2] = accel_val[2];

			motion_sample_ct++;

			if (is_motion_detected()) {
				module_listener(MOTION_ST_MOVEMENT);
			}

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
