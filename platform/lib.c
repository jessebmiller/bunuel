#include <stdbool.h>
#include <assert.h>

#include <SDL3/SDL.h>

#define BUNUEL_PIN_API_1
#define BUNUEL_STRIP_PREFIX
#include <bunuel.h>

#include "lib.h"

#define DEFAULT_WINDOW_TITLE "some Bunñuel app";

bool bunuel_open_window_v0(Window_v0 *window) {
	bool ok = SDL_Init(SDL_INIT_VIDEO);
	if (!ok) return false;

	if (!window->title) {
		window->title = DEFAULT_WINDOW_TITLE;
	}
	window->width = 800;
	window->height = 600;
	window->raw = SDL_CreateWindow(
		window->title,
		window->width,
		window->height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (window->raw == NULL) {
		error("NULL SDL_Window (%s)", window->title);
		return false;
	}

	window->renderer = SDL_CreateRenderer(window->raw, NULL);
	if (window->renderer == NULL) {
		error("NULL SDL_Renderer (%s)", window->title);
		return false;
	}

	return true;
}

void bunuel_close_window_v0(Window_v0 *window) {
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->raw);
}

bool bunuel_window_clear_v0(Window_v0 *window) {
	if (!SDL_SetRenderDrawColor(
		window->raw,
		window->bg_r,
		window->bg_g,
		window->bg_b,
		window->bg_a
	)) return false; 

	return SDL_RenderClear(window->renderer);
}

bool bunuel_window_draw_rect_v0(Window_v0 window,
 	size_t x, size_t y, size_t width, size_t height,
	RGB8_v0 c
) {
	SDL_SetRenderColor(window->renderer, c.r, c.g, c.b, c.a);
	SDL_Rect rect = {x, y, width, height};
	SDL_RenderRect(window->renderer, &rect);
}

bool bunuel_window_present_v0(Window_v0 *window) {
	return SDL_RenderPresent(window->renderer);
}

// TODO: When we implement GPU graphics and need the "begin" and "end"
//       for command batching consider requiring that we hold a 
//       "batch" type to do the draw calls then submit the batch to
//       make what's happening clear.

// EVENTS

char* bunuel_event_type_name_v0(EventType_v0 type) {
	switch(type) {
	case DO_NOTHING:        return "DO_NOTHING";
	case DO_QUIT:           return "DO_QUIT";
	case DID_WINDOW_RESIZE: return "DID_WINDOW_RESIZE";
	case EVENT_MAX:         return "EVENT_MAX";
	default: return "unknown_event_type";
	}
}

char* bunuel_event_name_v0(Event_v0 event) {
	return bunuel_event_type_name_v0(event.type);
}

static bool handle_sdl_event(Window_v0 *window, Event_v0 *event, SDL_Event *sdl_event) {
	switch(sdl_event->type) {
	case SDL_EVENT_QUIT: {
		event->type = DO_QUIT;
		debug("Got DO_QUIT event");
		return true;
	}
	case SDL_EVENT_WINDOW_RESIZED: {
		event->type = DID_WINDOW_RESIZE;
		window->width = sdl_event->window.data1;
		window->height = sdl_event->window.data2;
		debug("Window resized to %dx%d", window->width, window->height);
		return true;
	}
	default:
		debug("Unknown SDL_Event.type(%s)", sdl_event->type);
		return false;
	}
}

bool bunuel_event_take_v0(Window_v0 *window, Event_v0 *event) {
	SDL_Event sdl_event;
	if(!SDL_PollEvent(&sdl_event)) return 0;
	return handle_sdl_event(window, event, &sdl_event);
}

bool bunuel_event_wait_v0(Window_v0 *window, Event_v0 *event) {
	SDL_Event sdl_event;
	if(!SDL_WaitEvent(&sdl_event)) return 0;
	return handle_sdl_event(window, event, &sdl_event);
}

