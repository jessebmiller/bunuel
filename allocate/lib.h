#ifndef BUNUEL_ALLOCATOR_LIB_H
#define BUNUEL_ALLOCATOR_LIB_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

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

#endif // BUNUEL_ALLOCATOR_LIB_H
