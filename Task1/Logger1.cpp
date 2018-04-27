#pragma once
#include "stdafx.h"
#include "Logger1.h"


Logger1::Logger1():Logger("log.txt")
{
}


Logger1::~Logger1()
{
}

Logger* Logger1::Write(Event event) {
	time_t* ptime = &event.time;
	char* buf = asctime(localtime(ptime));
	f.open("log.txt", ios::app);
	f << "id: " << event.id << ", date: " << buf << ", p1=" << event.p1 << endl;
	f.flush();
	f.close();
	return this;
}
