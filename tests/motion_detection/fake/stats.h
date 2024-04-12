#ifndef _FAKE_STATS_H_
#define _FAKE_STATS_H_

#include <string.h>
#include <stdbool.h>

struct fake_stats {
	size_t count;
	void *call_order[30];
};

size_t fake_stats_call_count(struct fake_stats *stats,
			     void *api);

bool fake_stats_apis_called_in_order(struct fake_stats *stats,
				     void *apis[],
				     size_t len);

void fake_stats_teardown(struct fake_stats *stats);

void fake_stats_update(struct fake_stats *stats,
		       void *api_called);

#endif /* _FAKE_STATS_H_ */
