#include <zephyr/kernel.h>
#include <zephyr/ztest.h>
#include <motion_detection.h>

#include <fake/accel.h>
#include <fake/stats.h>

enum motion_st motion_st = MOTION_ST_INVALID;

void motion_detection_st_changed(enum motion_st st)
{
	printk("Motion state changed: %d\n", st);
	motion_st = st;
}

void testcase_before(void *unused)
{
}

void testcase_after(void *unused)
{
	motion_detection_teardown();
	motion_st = MOTION_ST_INVALID;
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

ZTEST(motion_detection_testsuite, test_motion_init_ok)
{
	int err;

	err = motion_detection_init();
	zassert_ok(err);
}

ZTEST(motion_detection_testsuite, test_motion_init_when_enabled_fails)
{
	int err;

	err = motion_detection_init();
	zassert_ok(err);

	err = motion_detection_init();
	zassert_equal(-EALREADY, err);
}

ZTEST(motion_detection_testsuite, test_motion_init_starts_engine)
{
	zassert_ok(motion_detection_init());
	zassert_true(motion_detection_is_enabled());
}

ZTEST(motion_detection_testsuite, test_motion_disabled_before_init)
{
	zassert_true(!motion_detection_is_enabled());
}

ZTEST(motion_detection_testsuite, test_motion_add_listener_succeeds)
{
	zassert_ok(motion_detection_listener_add(motion_detection_st_changed));
}

ZTEST(motion_detection_testsuite, test_motion_init_starts_with_uknown)
{
	zassert_ok(motion_detection_listener_add(motion_detection_st_changed));
	zassert_ok(motion_detection_init());
	zassert_equal(MOTION_ST_UNKNOWN, motion_st);
}
