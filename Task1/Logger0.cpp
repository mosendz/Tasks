#pragma once
#include "stdafx.h"
#include "Logger0.h"


Logger0::Logger0():Logger("log.txt")
{
}



Logger* Logger0::Write(Event event) {
	time_t* ptime = &event.time;
	char* buf = asctime(localtime(ptime));
	f.open("log.txt", ios::app);
	f << "id: " << event.id << ", date: " << buf;
	f.flush();
	f.close();
	return this;
}