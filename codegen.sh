#!/usr/bin/env bash

set -e

gen_fixed_set_v0() {
	T=$1
	CAP=$2
	PRE=$3

	cat <<EOF
/* ===========================================
THE FOLLOWING CODE IS GENERATED ON EVERY BUILD
YOUR EDITS WILL BE OVERWRITTEN
============================================*/
#include <stdbool.h>

typedef struct {
  ${T} items[${CAP}];
  int count;
} ${T}Set;
static inline bool ${PRE}_eq(${T} *a, ${T} *b);
static inline int ${PRE}_index(${T}Set *set, ${T} *item) {
  for (int i = 0; i < set->count; i++) {
    if (${PRE}_eq(&set->items[i], item))
      return i;
  }
  return -1;
}
static inline ${T} *
${PRE}_add(${T}Set *set, ${T} item) {
  int i = ${PRE}_index(set, &item);
  if (i >= 0)
    return &set->items[i];
  if (set->count >= ${CAP})
    return NULL;
  i = set->count;
  set->count += 1;
  set->items[i] = item;
  return &set->items[i];
}
static inline bool ${PRE}_remove(${T}Set *set, ${T} *item) {
  int i = ${PRE}_index(set, item);
  if (i < 0)
    return false;
  set->count -= 1;
  set->items[i] = set->items[set->count];
  return true;
}
static inline int ${PRE}_avail(${T}Set *set) {
  return ${CAP} - set->count;
}

EOF

}

