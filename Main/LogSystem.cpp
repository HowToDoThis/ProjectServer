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

void LogSystem::DevCon(const char* fmt, ...)
{
	if (developer->value)
	{
		const char* devMsg = "[DEBUG] ";
		char buffer[1024];
		sprintf(buffer, "%s%s", devMsg, fmt);

		va_list ap;
		char buf[1024];
		unsigned int len;

		va_start(ap, buffer);
		vsnprintf(buf, sizeof(buf), buffer, ap);
		va_end(ap);
		len = strlen(buf);
		if (len < sizeof(buf) - 2)		// -1 null, -1 for newline
			strcat(buf, "\n");
		else
			buf[len - 1] = '\n';

		ServerPrint(buf);
	}
	else
	{
		Console(fmt);
	}
}