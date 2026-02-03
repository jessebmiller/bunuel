#include "lib.h"

#define Arena_v0 bunuel_Arena_v0
#define Pool_v0 bunuel_Pool_v0

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
	pool->arena = bunuel_make_arena_v0(capacity, elem_size);

	return pool;
}

void bunuel_drop_pool_v0(Pool_v0* pool) {
	assert(pool != NULL);
	if(!pool) return;
	bunuel_drop_arena_v0(pool->arena);
	free(pool);
}

void bunuel_wipe_pool_v0(Pool_v0* pool) {
	pool->free_list = NULL;
	bunuel_wipe_arena_v0(pool->arena);
}

void* bunuel_take_pool_v0(Pool_v0* pool) {
	// bump arena if nothing in free list
	if (!pool->free_list) return bunuel_bump_arena_v0(pool->arena);
	
	// otherwise use the free list
	void* elem = pool->free_list;
	pool->free_list = *(void**)pool->free_list;
	return elem;
}

void bunuel_give_pool_v0(Pool_v0* pool, void* elem) {
	*(void**)elem = pool->free_list;
	pool->free_list = elem;
}
