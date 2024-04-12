#include <zephyr/kernel.h>
#include <zephyr/ztest.h>
#include <motion_detection.h>

#include <fake/accel.h>
#include <fake/stats.h>

void testcase_before(void *unused)
{
}

void testcase_after(void *unused)
{
}

ZTEST_SUITE(motion_detection_testsuite, NULL, NULL,
	    testcase_before, testcase_after, NULL);

ZTEST(motion_detection_testsuite, test_verify_fixture_installed)
{
	zassert_true(true);
}

/**
 * List of Tests
 * *************
 * 
 * - Initializing the Module starts the Motion Detection Engine.
 * - Initial State is Unknown.
 * - Callback is triggered on a state change.
 * - Accel is polled once a second.
 * - Transition to Idle state if no motion in 5 seconds.
 * - Transition to Movement state if Motion is sustained for 1 second.
 * - Once entered, stay in Movement state for 5 seconds.
 */
