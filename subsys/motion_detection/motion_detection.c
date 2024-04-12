#include <stdbool.h>
#include <zephyr/kernel.h>

bool motion_detect_enabled;

int motion_detection_init(void)
{
	if (motion_detect_enabled) {
		return -EALREADY;
	}
	motion_detect_enabled = true;

	return 0;
}

void motion_detection_teardown(void)
{
	motion_detect_enabled = false;
}
