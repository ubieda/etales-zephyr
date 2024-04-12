#ifndef _MOTION_DETECTION_H_
#define _MOTION_DETECTION_H_

#include <stdbool.h>

int motion_detection_init(void);
bool motion_detection_is_enabled(void);
void motion_detection_teardown(void);

#endif /* _MOTION_DETECTION_H_ */
