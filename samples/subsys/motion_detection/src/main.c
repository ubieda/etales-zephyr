#include <zephyr/kernel.h>
#include <motion_detection.h>

static char *motion_st_str(enum motion_st motion_st)
{
	char *rsp = NULL;

	switch(motion_st) {
	case MOTION_ST_IDLE:
		rsp = "IDLE";
		break;
	case MOTION_ST_INVALID:
		rsp  = "INVALID";
		break;
	case MOTION_ST_MOVEMENT:
		rsp  = "MOVEMENT";
		break;
	case MOTION_ST_UNKNOWN:
		rsp  = "UNKNOWN";
		break;
	}

	return rsp;
}

void motion_st_changed(enum motion_st st)
{
	printk("Motion State Changed! %s\n", motion_st_str(st));
}

int main(void)
{
	(void)motion_detection_listener_add(motion_st_changed);
	(void)motion_detection_init();

	printk("Motion Detection Sample Started!\n");

	return 0;
}
