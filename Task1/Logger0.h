#pragma once
#include "Logger.h"
class Logger0 :
	public Logger
{
public:
	Logger0();
	Logger * Write(Event event);
};

