#include "fake/stats.h"
#include <zephyr/kernel.h>

size_t fake_stats_call_count(struct fake_stats *stats, void *api)
{
	size_t call_count = 0;

	for (size_t i = 0 ; i < stats->count ; i++) {
		if (stats->call_order[i] == api) {
			call_count++;
		}
	}

	return call_count;
}

void fake_stats_update(struct fake_stats *stats, void *api_called)
{
	if (stats->count < ARRAY_SIZE(stats->call_order)) {
		stats->call_order[stats->count] = api_called;
		stats->count++;
	}
}

bool fake_stats_apis_called_in_order(struct fake_stats *stats, void *apis[], size_t len)
{
	for (size_t i = 0 ; i < MIN(stats->count, len) ; i++) {
		if (apis[i] != stats->call_order[i]) {
			return false;
		}
	}

	return true;
}

void fake_stats_teardown(struct fake_stats *stats)
{
	memset(stats, 0, sizeof(struct fake_stats));
}
