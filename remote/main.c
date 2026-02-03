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
	
	// TODO: write struct Window that is zero initialized
	Window window = {0};
	window.title = "/remote/";
	// TODO: write bool open_window(Window window);
	//       modifies window adding renderer, event queue, etc.
	//       uses good defaults (remember changing defaults can require a version bump)
	if(!open_window(&window)) {
		error("Could not open window. Exiting.");
		exit(-1);
	}

	bool running = true;
	while(running) {
		// TODO: write struct Event, zero initialized
		Event event;
		// TODO: write int take_event(Window *window, Event *event); returning the number of events ramaining in the queue
		while(take_event(&window, &event)) {
			debug("Got %s event", event_name(event));
			switch(event.type) {
			// TODO: make event type enum with DOs and DIDs to differentiate between intentions and occurences
			case DO_QUIT: {
				debug("Handling DO_QUIT");
				running = false;
			}
			break;
			case DID_WINDOW_RESIZE: {
				// TODO: make sure take_event updates the window based on changes to underlying implementation
				debug("Window resized to %dx%d", window.width, window.height);
			}
			break;
			default: {
				// TODO: write char* event_name(EventType type);
				devln("Uhandled event %s", event_name(event));
			}
		}
		// TODO: Write void clear(Window *window); That uses the window's set clear color (default black);
		clear(&window);
		// TODO: write bool present(Window *window, BackBuffer *buf); presents the buffer in the window
		present(&window);
	}
	// TODO: write bool close_window(Window window);
	close_window(&window);
	
	return 0;
}

