#include <assert.h>

#define BUNUEL_PIN_API_1
#define BUNUEL_STRIP_PREFIX
#include <bunuel.h>

#include "lib.h"

#define Window_v0       bunuel_Window_v0
#define open_window_v0  bunuel_open_window_v0
#define close_window_v0 bunuel_close_window_v0

#define Event_v0           bunuel_Event_v0
#define event_type_name_v0 bunuel_event_type_name_v0
#define event_name_v0      bunuel_event_name_v0

int main() {
	logln("Testing platform layer");
	Window_v0 window = {0};
	window.title = "test platform window";
	assert(open_window_v0(&window));
	assert(window.height);
	assert(window.width);
	assert(window.raw);
	assert(window.renderer);

	close_window_v0(&window);
	logln("PASS");
}
