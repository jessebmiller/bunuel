#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define BUNUEL_PIN_API_1
#define BUNUEL_STRIP_PREFIX
#include "./lib.h"

#define LOG_LEVEL_KEY "BUNUEL_LOG_LEVEL"

void check_str_match(char *a, char *b) {
	assert(strcmp(a, b) == 0);
}

int main() {

	logln("Testing Bunuel lib API Version 1");

	logln("");
	logln("log_level_name should describe the log level");
	logln("============================================");
	check_str_match(log_level_name(LOG_LEVEL_ERROR),   "ERROR");
	check_str_match(log_level_name(LOG_LEVEL_WARNING), "WARNING");
	check_str_match(log_level_name(LOG_LEVEL_INFO),    "INFO");
	check_str_match(log_level_name(LOG_LEVEL_DEBUG),   "DEBUG");
	check_str_match(log_level_name(LOG_LEVEL_UNKNOWN), "LOG_LEVEL_UNKNOWN");

	logln("");
	logln("Loggers should log at their level");
	logln("=================================");
	char *log_level_envar = getenv(LOG_LEVEL_KEY);

	logln("");
	logln("At ERROR log level, only errors should log");
	setenv(LOG_LEVEL_KEY, "ERROR", 1);
	error("- ERROR");
	warning("SHOULD NOT LOG");
	info("SHOULD NOT LOG");
	debug("SHOULD NOT LOG");

	logln("");
	logln("At WARNING log level, errors and warnings should log");
	setenv(LOG_LEVEL_KEY, "WARNING", 1);
	error("- ERROR");
	warning("- WARNING");
	info("SHOULD NOT LOG!");
	debug("SHOULD NOT LOG!");

	logln("");
	logln("At INFO log level, only debug should be silent");
	setenv(LOG_LEVEL_KEY, "INFO", 1);
	error("- ERROR");
	warning("- WARNING");
	info("- INFO");
	debug("SHOULD NOT LOG!");

	logln("");
	logln("At DEBUG log level, all levels should log");
	setenv(LOG_LEVEL_KEY, "DEBUG", 1);
	error("- ERROR");
	warning("- WARNING");
	info("- INFO");
	debug("- DEBUG");

	logln("");
	logln("At misconfigured log level, all levels should log");
	setenv(LOG_LEVEL_KEY, "aaaaa", 1);
	error("- ERROR");
	warning("- WARNING");
	info("- INFO");
	debug("- DEBUG");

	logln("");
	logln("At unset log level, all levels should log");
	unsetenv(LOG_LEVEL_KEY);
	error("- ERROR");
	warning("- WARNING");
	info("- INFO");
	debug("- DEBUG");

	if (log_level_envar) setenv(LOG_LEVEL_KEY, log_level_envar, 1);

	logln("");
	logln("logln should append a newline character");
	assert(logln("%s", "test") == 5);

	logln("Arenas can be made, dropped, wiped, and bumped");

	#define CAP 10
	Arena* a = make_arena(CAP, sizeof(int));
	assert(a != NULL);
	assert(a->capacity == CAP);
	assert(a->length == 0);
	assert(a->elem_size == sizeof(int));

	int* elems[CAP];
	for (int i = 0; i < CAP; i++) {
		elems[i] = bump_arena(a);
		assert(elems[i] != NULL);
		*elems[i] = i;
	}
	assert(a->length == CAP);
	for (int i = 0; i < CAP; i++) {
		assert(*elems[i] == i);
	}

	assert(bump_arena(a) == NULL);

	wipe_arena(a);
	assert(a != NULL);
	assert(a->capacity == CAP);
	assert(a->length == 0);
	assert(a->elem_size == sizeof(int));

	for (int i = 0; i < CAP; i++) {
		elems[i] = bump_arena(a);
		assert(elems[i] != NULL);
		*elems[i] = i;
	}
	assert(a->length == CAP);
	for (int i = 0; i < CAP; i++) {
		assert(*elems[i] == i);
	}

	drop_arena(a);

	Pool* p = make_pool(2, sizeof(size_t));
	assert(p != NULL);
	assert(p->free_list == NULL);

	size_t* x = take_pool(p);
	size_t* y = take_pool(p);
	assert(take_pool(p) == NULL);
	*x = 1;
	*y = 2;

	give_pool(p, y);
	size_t* z = take_pool(p);
	assert(z != NULL);
	assert(z == y);
	assert(take_pool(p) == NULL);

	logln("PASSED");
}

