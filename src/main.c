#include <stdio.h>
#include "entry.h"
#include "watch.h"

int32_t main () {
	watch *watch_ctx = init_watch (
				"bin/watch.so", (sym_table[]){
				{ .sym_name = "entry_main", .sym_addr = (void **)&entry_main},
				}, 1, entry_main); if (watch_ctx == NULL) return 1;
	return 0;
}
