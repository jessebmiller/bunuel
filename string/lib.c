#include <stdio.h>

#include "lib.h"
#include "../string/lib.h"

#define Str32_v0 bunuel_Str32_v0

Str32_v0 bunuel_join_str32_v0(Str32_v0 a, Str32_v0 b) {
	Str32_v0 j;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-truncation"
	(void)snprintf(j.text, sizeof(j.text), "%s%s", a.text, b.text);
#pragma GCC diagnostic pop
	return j;
}

