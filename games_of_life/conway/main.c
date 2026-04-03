#include <stdlib.h>
#include <stdio.h>

#define BUNUEL_STRIP_PREFIX
#define BUNUEL_PIN_API_1
#include <bunuel.h>

// TODO: make devln logger in bunuel that is removed in production builds
#define devln logln

// TODO: update bunuel.h with pin versions and stripped prefixes
#define window_draw bunuel_window_draw_v1
#define RGBA bunuel_RBGA_v0
#define DRAW_CMD_CLEAR BUNUEL_DRAW_CMD_CLEAR
#define DrawCommand bunuel_DrawCommand_v0
#define Clear bunuel_Clear_v0
#define Rect bunuel_Rect_v0

// handle_event handles an event then retuns true if the program should keep running
bool handle_event(Window *window, Event event) {
	devln("Got %s event", event_name(event));
	switch(event.type) {
	case DO_QUIT: {
	      debug("Handling DO_QUIT");
	      return false;
	} 
	case DID_WINDOW_RESIZE: {
		debug("Window resized to %dx%d", window->width, window->height);
		return true;
	} 
	default: 
		devln("Uhandled event %s", event_name(event));
		return true;
	}
}

#define BLOCKS 100

static void rand_grid(bool grid[BLOCKS][BLOCKS]) {
	for (int x = 0; x < BLOCKS; ++x) {
		for (int y = 0; y < BLOCKS; ++y) {
			grid[x][y] = rand() % 2;
		}
	}		
}

int main(int argc, char *argv[]) {
	printf("Starting");
	for(int i = 0; i < argc; ++i) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	
	Window window = {0};
	window.title = "/remote/";
	if(!open_window(&window)) {
		error("Could not open window. Exiting.");
		exit(-1);
	}

	int block_width = window.width / BLOCKS;
	int blocks_high = window-height / block_width;
	bool grid[BLOCKS][BLOCKS];
	rand_grid(&grid);

	bool running = true;
	while(running) {
		Event event;
		while(event_take(&window, &event)) {
			running = handle_event(&window, event);
			if (event.type = DID_WINDOW_RESIZE) {
				block_width = window.width / BLOCKS;
				blocks_high = window.height / block_width;
			}
		}
		window_draw(&window, clear(WHITE));
		for (int y = 0; y < blocks_high; ++y) {
			if ((y + 1) * block_width > window.height) break;
			for (int x = 0; x < BLOCKS; ++x) {
				if(!grid[x][y]) break;
				window_draw(&window, rect(x * block_width, y * block_width, block_width, block_width, black);
			}
		}
		window_present(&window);
	}

	close_window(&window);
	return 0;
}

