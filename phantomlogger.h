/*
* Copyright (c) 2012 Cleversoap
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef __PHANTOMLOGGER_H_
#define __PHANTOMLOGGER_H_

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)
	#define LOG_FUNCTION(tag,errorOut,format,...) phantomLog(tag,errorOut,format,##__VA_ARGS__);
#else
	#define LOG_FUNCTION(...)
#endif

#define TRACE(fmt,...) LOG_FUNCTION("TRACE",false,fmt,##__VA_ARGS__)
#define DEBUG(fmt,...) LOG_FUNCTION("DEBUG",false,fmt,##__VA_ARGS__)
#define WARN(fmt,...)  LOG_FUNCTION("WARN",false,fmt,##__VA_ARGS__)
#define ERROR(fmt,...) LOG_FUNCTION("ERROR",true,fmt,##__VA_ARGS__)
#define NET(fmt,...)   LOG_FUNCTION("NET",false,fmt,##__VA_ARGS__)
#define IO(fmt,...)    LOG_FUNCTION("IO",false,fmt,##__VA_ARGS__)

#if defined(_LOG_PRINT_) || defined(_LOG_FILE_)

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <time.h>

#ifdef _LOG_PRINT_
#include <mutex>
static std::mutex __log_mutex__;
#endif

static inline void phantomLog(const char* tag, bool errorOut, const char* format, ...)
{
	// Variable List
	va_list argptr;
	va_start(argptr, format);

	// Create log message
	char* msg;
	vasprintf(&msg, format, argptr);
	va_end(argptr);
	
	// Time
	timeval tv;
	gettimeofday(&tv, NULL);
        int ms = tv.tv_usec / 1000;

	static char timeBuffer[21];
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime); // Should this be system time?
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
	
#ifdef _LOG_PRINT_
	__log_mutex__.lock();
	(errorOut ? std::cerr : std::cout) << timeBuffer << "." << ms << "\t" << tag << "\t" << msg << std::endl;
	__log_mutex__.unlock();
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
