#include <stdlib.h>
#include <stdio.h>

#define BUNUEL_STRIP_PREFIX
#define BUNUEL_PIN_API_1
#include <bunuel.h>

// TODO: make devln logger in bunuel that is removed in production builds
#define devln logln

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
		while(event_take(&window, &event)) {
			running = handle_event(&window, event);
		}
		window_clear(&window);
		window_present(&window);
	}

	close_window(&window);
	return 0;
}

