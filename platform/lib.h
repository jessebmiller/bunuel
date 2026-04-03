#ifndef BUNUEL_PLATFORM_LIB_H
#define BUNUEL_PLATFORM_LIB_H

#include <stddef.h>
#include <stdint.h>

#include "draw_command.h"

// Window stuff

typedef struct {
	char *title;
	uint32_t width;
	uint32_t height;
	void *raw;
	void *renderer;
	bunuel_DrawCommand_v0[] draw_commands;
} bunuel_Window_v0;


bool bunuel_open_window_v0(bunuel_Window_v0 *window);
void bunuel_close_window_v0(bunuel_Window_v0 *window);

bool bunuel_window_draw_v0(
	bunuel_Window_v0 *window, bunuel_DrawCommand_v0 cmd);

bool bunuel_window_present_v0(bunuel_Window_v0 *window);

typedef enum {
	BUNUEL_DO_NOTHING = 0,
	BUNUEL_DO_QUIT,
	BUNUEL_DID_WINDOW_RESIZE,
	BUNUEL_EVENT_MAX,
} bunuel_EventType_v0;

typedef struct {
	bunuel_EventType_v0 type;
} bunuel_Event_v0;

char* bunuel_event_type_name_v0(bunuel_EventType_v0 type);
char* bunuel_event_name_v0(bunuel_Event_v0 event);

// event_take takes an event from the queue if there is one to take
bool
bunuel_event_take_v0(bunuel_Window_v0 *window, bunuel_Event_v0 *event);

// event_wait waits for an event then returns true if its recognized
bool
bunuel_event_wait_v0(bunuel_Window_v0 *window, bunuel_Event_v0 *event);

#endif // BUNUEL_PLATFORM_LIB_H
