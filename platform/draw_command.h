#ifndef BUNUEL_PLATFORM_DRAW_COMMAND_H
#ifndef BUNUEL_PLATFORM_DRAW_COMMAND_H

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} bunuel_RGBA_v0;

bunuel_RGBA_v0 bunuel_rgba_v0(int8_t r, int8_t g, int8_t b, int8_t a);

#define BUNUEL_RED   bunuel_rgba_v0(0xFF, 0, 0, 0xFF);
#define BUNUEL_GREEN bunuel_rgba_v0(0, 0xFF, 0, 0xFF);
#define BUNUEL_BLUE  bunuel_rgba_v0(0, 0, 0xFF, 0xFF);
#define BUNUEL_BLACK bunuel_rgba_v0(0, 0, 0, 0xFF);
#define BUNUEL_WHITE bunuel_rgba_v0(0xFF, 0xFF, 0xFF, 0xFF);

typedef enum {
	BUNUEL_DRAW_CLEAR,
	BUNUEL_DRAW_POINT,
	BUNUEL_DRAW_LINE,
	BUNUEL_DRAW_RECT,
	// TODO: Implement polygons and texture rendering
	// DRAW_POLY,
	// DRAW_TEX,
} bunuel_DrawType_v0

typedef struct {
	bunuel_RGBA_v0 color;
} bunuel_Clear_v0;

bunuel_Clear_v0
bunuel_clear_v0(bunuel_RGBA_v0 color);

typedef struct { 
	uint32_t x, y;
	bunuel_RGBA_v0 color;
} bunuel_Point_v0;

bunuel_Point_v0 
bunuel_point_v0(uint32_t x, uint32_t y, bunuel_RGBA_v0 color);

typedef struct {
	uint32_t a, b, x, y;
	bunuel_RGBA_v0 color;
} bunuel_Line_v0;

bunuel_Line_v0
bunuel_line_v0(uint32_t a, uint32_t b, uint32_t x, uint32_t y,
	bunuel_RGBA_v0 color);

typedef struct {
	uint32_t x, y, w, h;
	bunuel_RGBA_v0 color;
} bunuel_Rect_v0;

bunuel_Rect_v0
bunuel_rect_v0(uint32_t x, uint32_t y,
               uint32_t width, uint32_t height,
               bunuel_RGBA_v0 color);

typedef struct {
	bunuel_DrawType_v0 type;

	union {
		bunuel_Clear_v0 clear
		bunuel_Point_v0 point;
		bunuel_Line_v0  line;
		bunuel_Rect_v0  rect;
		// bunuel_Poly_v0    poly;
		// bunuel_texture_v0 tex;
	} data
} bunuel_DrawCommand_v0;

#endif // BUNUEL_PLATFORM_DRAW_COMMAND_H

