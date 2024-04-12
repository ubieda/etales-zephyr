#ifndef _MOTION_DETECTION_H_
#define _MOTION_DETECTION_H_

#include <stdbool.h>

enum motion_st {
	MOTION_ST_UNKNOWN,
};

typedef void (*motion_st_changed_t)(enum motion_st st);

int motion_detection_init(void);
int motion_detection_listener_add(motion_st_changed_t listener);
bool motion_detection_is_enabled(void);
void motion_detection_teardown(void);

#endif /* _MOTION_DETECTION_H_ */
