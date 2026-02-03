
/* ===========================================
THE FOLLOWING CODE IS GENERATED ON EVERY BUILD
YOUR EDITS WILL BE OVERWRITTEN
============================================*/
#include <stdbool.h>

typedef struct {
  int items[3];
  int count;
} intSet;
static inline bool int_set_eq(int *a, int *b);
static inline int int_set_index(intSet *set, int *item) {
  for (int i = 0; i < set->count; i++) {
    if (int_set_eq(&set->items[i], item))
      return i;
  }
  return -1;
}
static inline int *
int_set_add(intSet *set, int item) {
  int i = int_set_index(set, &item);
  if (i >= 0)
    return &set->items[i];
  if (set->count >= 3)
    return NULL;
  i = set->count;
  set->count += 1;
  set->items[i] = item;
  return &set->items[i];
}
static inline bool int_set_remove(intSet *set, int *item) {
  int i = int_set_index(set, item);
  if (i < 0)
    return false;
  set->count -= 1;
  set->items[i] = set->items[set->count];
  return true;
}
static inline int int_set_avail(intSet *set) {
  return 3 - set->count;
}

/* ===========================================
THE FOLLOWING CODE IS GENERATED ON EVERY BUILD
YOUR EDITS WILL BE OVERWRITTEN
============================================*/
#include <stdbool.h>

typedef struct {
  float items[3];
  int count;
} floatSet;
static inline bool float_set_eq(float *a, float *b);
static inline int float_set_index(floatSet *set, float *item) {
  for (int i = 0; i < set->count; i++) {
    if (float_set_eq(&set->items[i], item))
      return i;
  }
  return -1;
}
static inline float *
float_set_add(floatSet *set, float item) {
  int i = float_set_index(set, &item);
  if (i >= 0)
    return &set->items[i];
  if (set->count >= 3)
    return NULL;
  i = set->count;
  set->count += 1;
  set->items[i] = item;
  return &set->items[i];
}
static inline bool float_set_remove(floatSet *set, float *item) {
  int i = float_set_index(set, item);
  if (i < 0)
    return false;
  set->count -= 1;
  set->items[i] = set->items[set->count];
  return true;
}
static inline int float_set_avail(floatSet *set) {
  return 3 - set->count;
}

