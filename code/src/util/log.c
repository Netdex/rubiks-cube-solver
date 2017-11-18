#include <stdarg.h>
#include <stdio.h>

#include "util/log.h"

void logm(const char* file, const char* func, int line, const char* fmt, ...)
{
	char buf[256];
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	printf("%s:%d@%s(): %s\n", file, line, func, buf);
	va_end(args);
}