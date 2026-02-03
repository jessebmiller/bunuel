#ifndef BUNUEL_LOG_LIB_H
#define BUNUEL_LOG_LIB_H

typedef enum {
	BUNUEL_LOG_LEVEL_ERROR,
	BUNUEL_LOG_LEVEL_WARNING,
	BUNUEL_LOG_LEVEL_INFO,
	BUNUEL_LOG_LEVEL_DEBUG,
	BUNUEL_LOG_LEVEL_UNKNOWN,
} bunuel_LogLevel_v0;

char* bunuel_log_level_name_v0(bunuel_LogLevel_v0 log_level);

int bunuel_error_v0(const char *restrict fmt, ...);
int bunuel_warning_v0(const char *restrict fmt, ...);
int bunuel_info_v0(const char *restrict fmt, ...);
int bunuel_debug_v0(const char *restrict fmt, ...);

int bunuel_logln_v0(char* log);
int bunuel_logln_v1(const char *restrict format, ...);

#endif // BUNUEL_LOG_LIB_H
