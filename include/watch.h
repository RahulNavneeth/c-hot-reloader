#ifndef WATCH_H
#define WATCH_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
	char *sym_name;
	void **sym_addr;
} sym_table;

typedef struct {
	char *libname;
	sym_table *sym_t;
	size_t sym_c;
	void *handle;
} watch;

watch *init_watch (const char *libname, sym_table *sym_t, size_t sym_c, int32_t (*entry)(void));

#endif /* WATCH_H */
