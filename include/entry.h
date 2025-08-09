#ifndef ENTRY_H
#define ENTRY_H

#include <stdint.h>

typedef struct {
	char *description;
	int32_t version;
} entry ;

entry *init ();
void update_description (entry *ctx, const char *description);
void update_version (entry *ctx, int32_t version);
int32_t entry_main ();

#endif /* ENTRY_H */
