#pragma once
#include "stdafx.h"
#include "Logger.h"
#include "Logger0.h"
#include "Logger1.h"
#include "Logger2.h"
#include "Task1.h"
#include <fstream>

Logger::Logger(char* fileName)
{
	strcpy(filePath, fileName);
}

Logger::~Logger()
{
	f.close();
}

Logger* Logger::GetLogger(int level) 
{
	Logger* plog;
	switch (level) {
		case 0:
			plog = new Logger0();
			break;
		case 1:
			plog = new Logger1();
			break;
		case 2:
			plog = new Logger2();
			break;
		default:
			plog = new Logger0();
	}
	return plog;
}
