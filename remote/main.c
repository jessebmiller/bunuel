#include <stdlib.h>
#include <stdio.h>

#define BUNUEL_STRIP_PREFIX
#define BUNUEL_PIN_API_1
#include <bunuel.h>

// TODO: make devln logger in bunuel that is removed in production builds
#define devln logln

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

	bool running = true;
	while(running) {
		Event event;
		while(event_take(&event)) {
			debug("Got %s event", event_name(event));
			switch(event.type) {
			case DO_QUIT: {
				debug("Handling DO_QUIT");
				running = false;
			} break;
			case DID_WINDOW_RESIZE: {
				// TODO: make sure take_event updates the window based on changes to the raw window
				debug("Window resized to %dx%d", window.width, window.height);
			} break;
			default:
				devln("Uhandled event %s", event_name(event));
			}
			// TODO: implement target delta or fps aware wait
		}
		window_clear(&window);
		window_present(&window);
	}
	close_window(&window);
	
	return 0;
}

