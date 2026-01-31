#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define BUNUEL_STRIP_PREFIX
#include "./lib.h"

/*
typedef enum {
	BUNUEL_LOG_LEVEL_ERROR,
	BUNUEL_LOG_LEVEL_WARNING,
	BUNUEL_LOG_LEVEL_INFO,
	BUNUEL_LOG_LEVEL_DEBUG,
	BUNUEL_LOG_LEVEL_UNKNOWN,
} bunuel_LogLevel_v0;
*/

static LogLevel_v0 get_log_level() {
	char* level = getenv("BUNUEL_LOG_LEVEL");
	if (!level) return LOG_LEVEL_UNKNOWN;
	if (strcmp(level, "ERROR") == 0) {
		return LOG_LEVEL_ERROR;
	} else if (strcmp(level, "WARNING") == 0) {
		return LOG_LEVEL_WARNING;
	} else if (strcmp(level, "INFO") == 0) {
		return LOG_LEVEL_INFO;
	} else if (strcmp(level, "DEBUG") == 0) {
		return LOG_LEVEL_DEBUG;
	}
	return LOG_LEVEL_UNKNOWN;
}

char* bunuel_log_level_name_v0(LogLevel_v0 log_level) {
	switch(log_level) {	
	case(LOG_LEVEL_ERROR):   return "ERROR";
	case(LOG_LEVEL_WARNING): return "WARNING";
	case(LOG_LEVEL_INFO):    return "INFO";
	case(LOG_LEVEL_DEBUG):   return "DEBUG";
	case(LOG_LEVEL_UNKNOWN): return "LOG_LEVEL_UNKNOWN";
	default: assert(false && "UNREACHABLE");
	}
}

static int vlogln_level(
		LogLevel_v0 log_level,
		const char *restrict fmt,
		va_list args
) {
	int printed = 0;
	if (log_level > get_log_level()) return printed;
	printed += printf("%s ", bunuel_log_level_name_v0(log_level));
	printed += vprintf(fmt, args);
	putchar('\n');
	printed += 1;
	return printed;
}

#define DEF_LOGGER(name, LOG_LEVEL) \
int name(const char *restrict format, ...) {\
	va_list args;\
	va_start(args, format);\
	int printed = vlogln_level(LOG_LEVEL, format, args);\
	va_end(args);\
	return printed;\
}

DEF_LOGGER(bunuel_error_v0, LOG_LEVEL_ERROR)
DEF_LOGGER(bunuel_warning_v0, LOG_LEVEL_WARNING)
DEF_LOGGER(bunuel_info_v0, LOG_LEVEL_INFO)
DEF_LOGGER(bunuel_debug_v0, LOG_LEVEL_DEBUG)

int bunuel_logln_v0(char* log) {
	return printf("%s\n", log);
}

int bunuel_logln_v1(const char *restrict fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int printed = vprintf(fmt, args);
	putchar('\n');
	printed += 1;
	return printed;
}

Arena_v0* bunuel_make_arena_v0(size_t capacity, size_t elem_size) {
	int size = capacity * elem_size;
	size += sizeof(Arena_v0);
	Arena_v0* arena = malloc(size);
	if (!arena) return NULL;
	
	arena->elem_size = elem_size;
	arena->length = 0;
	arena->capacity = capacity;
	
	return arena;
}

void bunuel_drop_arena_v0(Arena_v0* arena) {
	free(arena);
}

void bunuel_wipe_arena_v0(Arena_v0* arena) {
	arena->length = 0;
}

void* bunuel_bump_arena_v0(Arena_v0* arena) {
	assert(arena->length <= arena->capacity);
	if (arena->length >= arena->capacity) return NULL;

	char* block = arena->data + (arena->length * arena->elem_size); 
	arena->length += 1;
	return (void*)block;
}

Pool_v0* bunuel_make_pool_v0(size_t capacity, size_t elem_size) {
	assert(elem_size >= sizeof(void*));
	if (elem_size < sizeof(void*)) return NULL;

	Pool_v0* pool = malloc(sizeof(Pool_v0));
	if (!pool) return NULL;

	pool->free_list = NULL;
	pool->arena = make_arena_v0(capacity, elem_size);

	return pool;
}

void bunuel_drop_pool_v0(Pool_v0* pool) {
	assert(pool != NULL);
	if(!pool) return;
	drop_arena_v0(pool->arena);
	free(pool);
}

void bunuel_wipe_pool_v0(Pool_v0* pool) {
	pool->free_list = NULL;
	wipe_arena_v0(pool->arena);
}

void* bunuel_take_pool_v0(Pool_v0* pool) {
	// bump arena if nothing in free list
	if (!pool->free_list) return bump_arena_v0(pool->arena);
	
	// otherwise use the free list
	void* elem = pool->free_list;
	pool->free_list = *(void**)pool->free_list;
	return elem;
}

void bunuel_give_pool_v0(Pool_v0* pool, void* elem) {
	*(void**)elem = pool->free_list;
	pool->free_list = elem;
}
