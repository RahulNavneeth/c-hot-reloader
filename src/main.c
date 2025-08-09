#include <stdio.h>
#include "entry.h"
#include "watch.h"

int32_t main () {
	entry *ctx = init(); if (ctx == NULL) return 1;
	watch *watch_ctx = init_watch (
				"watch.so", (sym_table[]){
				{ .sym_name = "entry_main", .sym_addr = (void **)&entry_main},
				}, 1); if (watch_ctx == NULL) return 1;
	return 0;
}
