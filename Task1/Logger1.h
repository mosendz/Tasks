#pragma once
#include "Logger.h"
class Logger1 :
	public Logger
{
public:
	Logger1();
	~Logger1();
	Logger * Write(Event event);
};

