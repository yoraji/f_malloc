#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

static void *(*real_malloc)(size_t) = NULL;
static int fail_line = -1;
static int failed_once = 0;

static void init_real_malloc() {
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
        if (!real_malloc) {
            fprintf(stderr, "Error: Failed to resolve real malloc\n");
            exit(1);
        }
    }
}

void *__debug_malloc(size_t size, const char *file, int line) {
    init_real_malloc(); // Ensure real malloc is initialized
    if (fail_line == -1) {
        char *env = getenv("FAIL_LINE");
        if (env) {
            fail_line = atoi(env);
        }
    }
    // Fail malloc **only once** if it matches the requested line
    if (fail_line == line && !failed_once) {
        fprintf(stderr, "[DEBUG] malloc failed at %s:%d (size: %zu)\n", file, line, size);
        failed_once = 1;
        return NULL;
    }
    // Call the real malloc
    return real_malloc(size);
}

// Macro to capture file & line information
#define malloc(size) __debug_malloc(size, __FILE__, __LINE__)