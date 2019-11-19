#include "shared/Main.h"

void LogSystem::Console(const char* fmt, ...)
{
	va_list ap;
	char buf[1024];
	unsigned int len;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	len = strlen(buf);
	if (len < sizeof(buf) - 2)		// -1 null, -1 for newline
		strcat(buf, "\n");
	else
		buf[len - 1] = '\n';

	ServerPrint(buf);
}