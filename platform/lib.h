#ifndef BUNUEL_PLATFORM_LIB_H
#define BUNUEL_PLATFORM_LIB_H

#include <stddef.h>
#include <SDL3/SDL.h>

typedef struct {
	char *title;
	size_t width;
	size_t height;
	SDL_Window *raw;
	SDL_Renderer *renderer;
} bunuel_Window_v0;

bool bunuel_open_window_v0(bunuel_Window_v0 *window);
void bunuel_close_window_v0(bunuel_Window_v0 *window);

typedef enum {
	BUNUEL_DO_NOTHING = 0,
	BUNUEL_DO_QUIT,
	BUNUEL_DID_WINDOW_RESIZE,
	BUNUEL_DID_MAX,
} bunuel_EventType_v0;

typedef struct {
	bunuel_EventType_v0 type;
} bunuel_Event_v0;

char* bunuel_event_type_name_v0(bunuel_EventType_v0 type);
char* bunuel_event_name_v0(bunuel_Event_v0 event);

int
bunuel_take_event_v0(bunuel_Window_v0 *window, bunuel_Event_v0 *event);

bool
bunuel_wait_event_v0(bunuel_Window_v0 *window, bunuel_Event_v0 *event);

#endif // BUNUEL_PLATFORM_LIB_H
