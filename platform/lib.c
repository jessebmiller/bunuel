#include <stdbool.h>
#include <assert.h>

#include <SDL3/SDL.h>

#define BUNUEL_PIN_API_1
#define BUNUEL_STRIP_PREFIX
#include <bunuel.h>
#include <lib.h>

#define Window_v0 bunuel_Window_v0

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
