#pragma once
#include "Task1.h"

class Logger
{
protected:
	Logger(char* fileName);
	~Logger();
	char filePath[100];
	ofstream f;
public:
	static Logger* GetLogger(int level);
	virtual Logger* Write(Event event) = 0;
};
