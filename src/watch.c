#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>
#include "watch.h"

time_t get_mtime (const char *path) {
	struct stat st;
	return stat (path, &st) == 0 ? st.st_mtime : 0;
}

watch *init_watch(const char *libname, sym_table *sym_t, size_t sym_c, int32_t (*entry)(void)) {
    static watch *singleton;
    if (!singleton) {
        singleton = malloc(sizeof(watch));
        if (!singleton) return NULL;
        singleton->libname = strdup(libname);
        singleton->sym_t = sym_t;
        singleton->sym_c = sym_c;
        singleton->handle = NULL;
    }

    time_t last_mtime = 0;
    while (1) {
        time_t mtime = get_mtime(singleton->libname);
        if (mtime != last_mtime) {
            last_mtime = mtime;
            if (singleton->handle) dlclose(singleton->handle);
            singleton->handle = dlopen(singleton->libname, RTLD_LAZY);
            if (!singleton->handle) {
                printf("Err: %s\n", dlerror());
                return NULL;
            }
            for (size_t c = 0; c < singleton->sym_c; c++) {
                *singleton->sym_t[c].sym_addr = dlsym(singleton->handle, singleton->sym_t[c].sym_name);
            }
            if (entry && entry()) {
                break;
            }
        }
        usleep(200000);
    }
    return singleton;
}
