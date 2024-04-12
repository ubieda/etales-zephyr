#include <zephyr/kernel.h>
#include <motion_detection.h>

bool motion_detect_enabled;
motion_st_changed_t module_listener;

int motion_detection_init(void)
{
	if (motion_detect_enabled) {
		return -EALREADY;
	}
	motion_detect_enabled = true;

	module_listener(MOTION_ST_UNKNOWN);

	return 0;
}

bool motion_detection_is_enabled(void)
{
	return motion_detect_enabled;
}

void motion_detection_teardown(void)
{
	motion_detect_enabled = false;
}

int motion_detection_listener_add(motion_st_changed_t listener)
{
	module_listener = listener;

	return 0;
}
