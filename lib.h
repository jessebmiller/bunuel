/**
 * Versioning in this library
 *
 * Function names are all versioned allowing
 * their APIs to be completely stable.
 *
 * As the functions evolve the old versions won't retire
 * New versions of those functions will be added as the 
 * need presents itself
 *
 * The library itself is versioned. Whenever a new
 * version of a function is added (say bunuel_func_v2)
 * a new BUNUEL_PIN_API_X check will be added
 *
 * Pin a version by defining BUNUEL_PIN_API_X where
 * X is the version number you want to use
 *
 * You can define aliases in client code to mix and match
 * function versions if you like.
 *
 * Developing this library
 *
 * When you add a new v0 interface, add its name macro
 * to all BUNUEL_PIN_API_X ifdef blocks. Add its stripped
 * prefix alias (for both versioned and unversioned names)
 * to the BUNUEL_STRIP_PREFIX block
 *
 * When you increment a function interface (add a v1, v2 et.c)
 * add a new BUNUEL_PIN_API_X ifdef block copying the previous
 * block but with your new function version(s)
 *
 * Add new pin api blocks above previous ones
 **/

#ifndef BUNUEL_LIB_H
#define BUNUEL_LIB_H

#include <stddef.h>

typedef enum {
	BUNUEL_LOG_LEVEL_ERROR,
	BUNUEL_LOG_LEVEL_WARNING,
	BUNUEL_LOG_LEVEL_INFO,
	BUNUEL_LOG_LEVEL_DEBUG,
	BUNUEL_LOG_LEVEL_UNKNOWN,
} bunuel_LogLevel_v0;

char* bunuel_log_level_name_v0(bunuel_LogLevel_v0 log_level);

int bunuel_error_v0(const char *restrict fmt, ...);
int bunuel_warning_v0(const char *restrict fmt, ...);
int bunuel_info_v0(const char *restrict fmt, ...);
int bunuel_debug_v0(const char *restrict fmt, ...);

int bunuel_logln_v0(char* log);
int bunuel_logln_v1(const char *restrict format, ...);

typedef struct {
	size_t elem_size;
	size_t length;
	size_t capacity;
	char data[];
} bunuel_Arena_v0;

bunuel_Arena_v0* bunuel_make_arena_v0(size_t capacity, size_t elem_size);
void bunuel_drop_arena_v0(bunuel_Arena_v0* arena_v0);
void bunuel_wipe_arena_v0(bunuel_Arena_v0* arena_v0);
void* bunuel_bump_arena_v0(bunuel_Arena_v0* arena_v0);

typedef struct {
	void* free_list;
	bunuel_Arena_v0* arena;
} bunuel_Pool_v0;

bunuel_Pool_v0* bunuel_make_pool_v0(size_t capacity, size_t elem_size);
void bunuel_drop_pool_v0(bunuel_Pool_v0* pool_v0);
void bunuel_wipe_pool_v0(bunuel_Pool_v0* pool_v0);
void* bunuel_take_pool_v0(bunuel_Pool_v0* pool_v0);
void bunuel_give_pool_v0(bunuel_Pool_v0* pool_v0, void* elem);

#ifdef BUNUEL_PIN_API_1

	#define bunuel_Arena bunuel_Arena_v0
	#define bunuel_make_arena bunuel_make_arena_v0
	#define bunuel_drop_arena bunuel_drop_arena_v0
	#define bunuel_wipe_arena bunuel_wipe_arena_v0
	#define bunuel_bump_arena bunuel_bump_arena_v0

	#define bunuel_Pool bunuel_Pool_v0
	#define bunuel_make_pool bunuel_make_pool_v0
	#define bunuel_drop_pool bunuel_drop_pool_v0
	#define bunuel_wipe_pool bunuel_wipe_pool_v0
	#define bunuel_take_pool bunuel_take_pool_v0
	#define bunuel_give_pool bunuel_give_pool_v0

	#define bunuel_error bunuel_error_v0
	#define bunuel_warning bunuel_warning_v0
	#define bunuel_info bunuel_info_v0
	#define bunuel_debug bunuel_debug_v0
	#define bunuel_log_level_name bunuel_log_level_name_v0
	#define bunuel_LogLevel bunuel_LogLevel_v0
	#define bunuel_logln bunuel_logln_v1
#endif // BUNUEL_PIN_API_1

#ifdef BUNUEL_PIN_API_0
	
	#define bunuel_Arena bunuel_Arena_v0
	#define bunuel_make_arena bunuel_make_arena_v0
	#define bunuel_drop_arena bunuel_drop_arena_v0
	#define bunuel_wipe_arena bunuel_wipe_arena_v0
	#define bunuel_bump_arena bunuel_bump_arena_v0

	#define bunuel_Pool bunuel_Pool_v0
	#define bunuel_make_pool bunuel_make_pool_v0
	#define bunuel_drop_pool bunuel_drop_pool_v0
	#define bunuel_wipe_pool bunuel_wipe_pool_v0
	#define bunuel_take_pool bunuel_take_pool_v0
	#define bunuel_give_pool bunuel_give_pool_v0

	#define bunuel_error bunuel_error_v0
	#define bunuel_warning bunuel_warning_v0
	#define bunuel_info bunuel_info_v0
	#define bunuel_debug bunuel_debug_v0
	#define bunuel_log_level_name bunuel_log_level_name_v0
	#define bunuel_LogLevel bunuel_LogLevel_v0
	#define bunuel_logln bunuel_logln_v0
#endif // BUNUEL_PIN_API_0

#ifdef BUNUEL_STRIP_PREFIX
	
	#define Arena bunuel_Arena
	#define make_arena bunuel_make_arena
	#define drop_arena bunuel_drop_arena
	#define wipe_arena bunuel_wipe_arena
	#define bump_arena bunuel_bump_arena

	#define Pool bunuel_Pool
	#define make_pool bunuel_make_pool
	#define drop_pool bunuel_drop_pool
	#define wipe_pool bunuel_wipe_pool
	#define take_pool bunuel_take_pool
	#define give_pool bunuel_give_pool

	#define Arena_v0 bunuel_Arena_v0
	#define make_arena_v0 bunuel_make_arena_v0
	#define drop_arena_v0 bunuel_drop_arena_v0
	#define wipe_arena_v0 bunuel_wipe_arena_v0
	#define bump_arena_v0 bunuel_bump_arena_v0

	#define Pool_v0 bunuel_Pool_v0
	#define make_pool_v0 bunuel_make_pool_v0
	#define drop_pool_v0 bunuel_drop_pool_v0
	#define wipe_pool_v0 bunuel_wipe_pool_v0
	#define take_pool_v0 bunuel_take_pool_v0
	#define give_pool_v0 bunuel_give_pool_v0

	#define LOG_LEVEL_ERROR BUNUEL_LOG_LEVEL_ERROR
	#define LOG_LEVEL_WARNING BUNUEL_LOG_LEVEL_WARNING
	#define LOG_LEVEL_INFO BUNUEL_LOG_LEVEL_INFO
	#define LOG_LEVEL_DEBUG BUNUEL_LOG_LEVEL_DEBUG
	#define LOG_LEVEL_UNKNOWN BUNUEL_LOG_LEVEL_UNKNOWN
	
	#define error bunuel_error
	#define warning bunuel_warning
	#define info bunuel_info
	#define debug bunuel_debug
	
	#define error_v0 bunuel_error_v0
	#define warning_v0 bunuel_warning_v0
	#define info_v0 bunuel_info_v0
	#define debug_v0 bunuel_debug_v0

	#define log_level_name bunuel_log_level_name
	#define log_level_name_v0 bunuel_log_level_name_v0

	#define LogLevel bunuel_LogLevel
	#define LogLevel_v0 bunuel_LogLevel_v0

	#define logln bunuel_logln
	#define logln_v0 bunuel_logln_v0
	#define logln_v1 bunuel_logln_v1

#endif // BUNUEL_STRIP_PREFIX

#endif // BUNUEL_LIB_H
