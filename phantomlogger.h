#ifndef __PHANTOMLOGGER_H_
#define __PHANTOMLOGGER_H_

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)
	#define LOG_FUNCTION(tag,format,...) phantomLog(tag,format,##__VA_ARGS__);
#else
	#define LOG_FUNCTION(...)
#endif

#define TRACE(fmt,...) LOG_FUNCTION("TRACE",fmt,##__VA_ARGS__)
#define DEBUG(fmt,...) LOG_FUNCTION("DEBUG",fmt,##__VA_ARGS__)
#define WARN(fmt,...)  LOG_FUNCTION("WARN",fmt,##__VA_ARGS__)
#define ERROR(fmt,...) LOG_FUNCTION("ERROR",fmt,##__VA_ARGS__)
#define NET(fmt,...)   LOG_FUNCTION("NET",fmt,##__VA_ARGS__)
#define IO(fmt,...)    LOG_FUNCTION("IO",fmt,##__VA_ARGS__)

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)

#include <iostream>
#include <fstream>
#include <time.h>

static inline void phantomLog(const char* tag, const char* format, ...)
{
	// Variable List
	va_list argptr;
	va_start(argptr, format);

	// Create log message
	char* msg;
	vasprintf(&msg, format, argptr);
	va_end(argptr);
	
	// Time
	static char timeBuffer[19];
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime); // Should this be system time?
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
	
#ifdef _LOG_PRINT_
	std::cout << timeBuffer << "\t" << tag << "\t" << msg << std::endl;
#endif

#ifdef _LOG_FILE_
	#define LFX(tok) #tok
	#define LFS(tok) LFX(tok)
	#define _LOG_FILE_STR_ LFS(_LOG_FILE_)
	std::ofstream lf;
	lf.open(_LOG_FILE_STR_, std::ios::out | std::ios::app);
	lf << timeBuffer << "\t" << tag << "\t" << msg << std::endl;
	lf.close();
#endif
	delete msg;
}

#endif

#endif
