#include <assert.h>

#define BUNUEL_PIN_API_0
#define BUNUEL_STRIP_PREFIX
#include "./lib.h"

int main() {

	logln("Testing Bunuel lib API Version 0");

	logln("logln should append a newline character");
	assert(logln("test") == 5);

	logln("PASSED");
}

