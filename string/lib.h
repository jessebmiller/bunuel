#ifndef BUNUEL_STRING_LIB_H
#define BUNUEL_STRING_LIB_H

typedef struct {
	size_t length;
	size_t capacity;
	char *data;
} bunuel_Str_v0;

typedef struct {
	char text[32];
} bunuel_Str32_v0;

bunuel_Str32_v0 bunuel_join_str32_v0(
	bunuel_Str32_v0 a, bunuel_Str32_v0 b);

#endif // BUNUEL_STRING_LIB_H
