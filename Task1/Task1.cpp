// Task1.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "Task1.h"
#include "Logger.h"
#include "Logger0.h"
#include "Logger1.h"
#include "Logger2.h"

using namespace std;

HANDLE ev;

extern HANDLE event_thread;
HANDLE logger_thread;

extern const int MAX_ARGS = 256;
extern double avg_interval;
extern int event_count;
char *argv[MAX_ARGS];
char* arg;
extern exponential_distribution<double> expdist;
extern CRITICAL_SECTION csexp;
extern int loggerlevel;
bool stop = false;

unsigned int __stdcall EventGenerator(void* lpParam) {
	HANDLE wPipe = *(HANDLE*)lpParam;
	default_random_engine generator;
	bernoulli_distribution dist1(0.5);
	binomial_distribution<int> dist2(10, 0.5);
	geometric_distribution<int> dist3(0.1);
	
	ev = CreateEvent(NULL, FALSE, FALSE, NULL);

	while (!stop) {
		EnterCriticalSection(&csexp);
		int interval = expdist(generator);
		LeaveCriticalSection(&csexp);
		Sleep(interval);
		int p1 = dist1(generator);
		int p2 = dist2(generator);
		int p3 = dist3(generator);
		Event e = { p1, p2, p3, event_count, time(NULL)};
		++event_count;
		WriteFile(wPipe, &e, sizeof(e), NULL, NULL);
		SetEvent(ev);
	}
	return 0;

}

unsigned int __stdcall LoggerThread(LPVOID lpParam) {
	
	Logger* loggers[3];
	loggers[0] = Logger::GetLogger(0);
	loggers[1] = Logger::GetLogger(1);
	loggers[2] = Logger::GetLogger(2);
	HANDLE rPipe = *(HANDLE*)lpParam;
	Event e;
	while (!stop) {
		WaitForSingleObject(ev, INFINITE);

		if (ReadFile(rPipe, &e, sizeof(e), NULL, NULL)) {
			loggers[loggerlevel]->Write(e);
		};
	}
	return 0;
}


int main()
{
	avg_interval = 1000;
	event_count = 0;
	expdist = exponential_distribution<double>(1.0 / avg_interval);
	crmap m = init_map();
	InitializeCriticalSection(&csexp);
	HANDLE wPipe, rPipe;
	CreatePipe(&rPipe, &wPipe, NULL, 1024);
	event_thread = (HANDLE)_beginthreadex(NULL, 0, EventGenerator, &wPipe, 0, NULL);
	logger_thread = (HANDLE)_beginthreadex(NULL, 0, LoggerThread, &rPipe, 0, NULL);
	
	while (true) {
		cout << "> ";
		int argc = read_args(argv);
		if (!argc) {
			continue;
		}
		string command(argv[0]);
		if (argc == 1) arg = NULL; else arg = argv[1];
		crmap::iterator it = m.find(command);
		if (it != m.end()) {
			it->second(arg);
		}else {
			cerr << "Unknown command" << endl;
		}
	}
    return 0;
}

