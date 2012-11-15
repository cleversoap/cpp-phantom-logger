#ifndef __PHANTOMLOGGER_H_
#define __PHANTOMLOGGER_H_

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)

#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>

static inline char* currentTime()
{
	static char buffer[19];
	time_t rawTime;
	struct tm* timeInfo;

	time(&rawTime);
	timeInfo = localtime(&rawTime); // Should this be system time?

	strftime(buffer, 19, "%Y-%m-%d %H:%M:%S", timeInfo);
	return buffer;
}

static inline void phantomLog(char* tag, const char* format, ...)
{
	// Variable List
	
	// Create log message
	
#ifdef _LOG_PRINT
	std::cout << currentTime() << "\t" << tag << "\t" << msg << std::endl;
#endif

#ifdef _LOG_FILE_
	// Write to file
#endif
}

#endif

#endif
