#ifndef __PHANTOMLOGGER_H_
#define __PHANTOMLOGGER_H_

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)
	#define LOG_FUNCTION(tag,format,...) phantomLog(tag,format,##__VA_ARGS__);
#else
	#define LOG_FUNCTION(...)
#endif

#define TRACE(fmt,...)		LOG_FUNCTION("TRACE",fmt,##__VA_ARGS__)
#define DEBUG(fmt,...)		LOG_FUNCTION("DEBUG",fmt,##__VA_ARGS__)
#define WARN(fmt,...)		LOG_FUNCTION("WARN",fmt,##__VA_ARGS__)
#define ERROR(fmt,...)		LOG_FUNCTION("ERROR",fmt,##__VA_ARGS__)
#define NET(fmt,...)		LOG_FUNCTION("NET",fmt,##__VA_ARGS__)
#define IO(fmt,...)			LOG_FUNCTION("IO",fmt,##__VA_ARGS__)

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
	va_list argptr;
	va_start(argptr, format);

	// Create log message
	char msg[256];
	vsnprintf(msg, sizeof(msg), format, argptr);
	va_end(argptr);
	
#ifdef _LOG_PRINT_
	std::cout << currentTime() << "\t" << tag << "\t" << msg << std::endl;
#endif

#ifdef _LOG_FILE_
	/*
	int fd = open(_LOG_FILE_, O_WRONLY);
	pwrite(fd, write_buffer, sizeof(write_buffer));
	close(fd);
	*/
#endif
}

#endif
