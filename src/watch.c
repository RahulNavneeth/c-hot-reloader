#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include "watch.h"

watch *init_watch (const char *libname, sym_table *sym_t, size_t sym_c) {
	static watch *singleton;
	if (singleton == NULL) {
		singleton = (watch*)malloc(sizeof(watch));
		if (singleton == NULL) return NULL;
		singleton->libname = strdup (libname);
		singleton->sym_t = sym_t;
		singleton->sym_c = sym_c;
		singleton->handle = dlopen (singleton->libname, RTLD_LAZY);
		
		if (singleton->handle == NULL) {
			printf ("Err: %s\n", dlerror ());
			return NULL;
		}

		for (size_t c = 0 ; c < singleton->sym_c ; c++) {
			singleton->sym_t[c].sym_addr = dlsym (singleton->handle, singleton->sym_t[c].sym_name);
		}

	}
	return singleton;
}
