#include "debug.h"
#include "fnasso.h"
#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>


char *str_lvl(int lvl)
{
	switch (lvl)
	{
		case FNASSO_FUNC_TRACE_DEBUG: return "FTD";
		case FNASSO_DEBUG: return "DBG";
		case FNASSO_EVENT: return "EVT";
		case FNASSO_WARN: return "WRN";
		case FNASSO_ERROR: return "ERR";
		default: "???";
	}
}

void fnasso_printf(int lvl, const char* fooname, const char *fmt, ...)
{
#ifndef TRACE_MODE
	if (lvl == FNASSO_FUNC_TRACE_DEBUG) return;
#endif
	
	va_list ap;
	va_start(ap, fmt);
	int i;
	char line[4092];
	
#ifdef DEBUG_MODE
	printf("@%lu [%s] %s: ", pthread_self(), str_lvl(lvl), fooname);
#else
	printf("[%s] %s: ", str_lvl(lvl), fooname);
#endif
	
	memset(line, 0, sizeof(line));
	vsprintf(line, fmt, ap);
	
	for (i = 0 ; i < strlen(line); i++)
	{
		if (line[i] == '\n')
			line[i] = ' ';
	}
	
	printf("%s\n", line);

	va_end(ap);
}

void fnasso_func_start(const char *fooname)
{
	fnasso_printf(FNASSO_FUNC_TRACE_DEBUG, fooname, "");
}

void fnasso_func_end(int level, const char *fooname, int status)
{
	fnasso_printf(level, fooname, "exit status (%d)", status);
}


