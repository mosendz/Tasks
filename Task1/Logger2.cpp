#pragma once
#include "stdafx.h"
#include "Logger2.h"


Logger2::Logger2():Logger("log.txt")
{
}


Logger2::~Logger2()
{
}

Logger* Logger2::Write(Event event) {
	time_t* ptime = &event.time;
	char* buf = asctime(localtime(ptime));
	f.open("log.txt", ios::app);
	f << "id: " << event.id << ", date: " << buf << ", p1=" << event.p1 << ", p2=" << event.p2 << ", p3=" << event.p3 << endl;
	f.flush();
	f.close();
	return this;
}
