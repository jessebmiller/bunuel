#ifndef BUNUEL_PLATFORM_LIB_H
#define BUNUEL_PLATFORM_LIB_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
	char *title;
	size_t width;
	size_t height;
	uint8_t bg_r;
	uint8_t bg_g;
	uint8_t bg_b;
	uint8_t bg_a;
	void *raw;
	void *renderer;
} bunuel_Window_v0;

bool bunuel_open_window_v0(bunuel_Window_v0 *window);
void bunuel_close_window_v0(bunuel_Window_v0 *window);

bool bunuel_window_clear_v0(bunuel_Window_v0 *window);
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

// event_take gets an event if there is one ready. Non blocking
bool
bunuel_event_take_v0(bunuel_Event_v0 *event);

// event_wait waits for an event then returns true if its recognized
bool
bunuel_event_wait_v0(bunuel_Event_v0 *event);

#endif // BUNUEL_PLATFORM_LIB_H
