#include "entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

entry *init () {
	static entry *singleton;
	if (singleton == NULL) {
		singleton = (entry*)malloc(sizeof(entry));
		if (singleton == NULL) return NULL;
		singleton->description = strdup ("Sample entry program for hot reloading!!!");
		singleton->version = 1;
	}
	return singleton;
} 

void update_description (entry *ctx, const char *description) {
	if (ctx->description) free (ctx->description);
	ctx->description = strdup (description);
}

void update_version (entry *ctx, int32_t version) {
	ctx->version = version;
}

int32_t entry_main () {
	entry *ctx = init(); if (ctx == NULL) return 1;
	// int32_t i = 0;
	// while (1) {
	// 	if (i++ & 1) {
			printf ("description: %s\nversion: %d\n", ctx->description, ctx->version);
	// 		sleep (1);
	// 	}
	// }
	return 0;
}
