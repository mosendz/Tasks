#pragma once
#include "Logger.h"
class Logger2 :
	public Logger
{
public:
	Logger2();
	~Logger2();
	Logger * Write(Event event);
};

