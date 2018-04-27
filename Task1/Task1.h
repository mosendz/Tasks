#pragma once
#include <iostream>
#include <algorithm>
#include <fcntl.h>
#include <algorithm>
#include <cctype>
#include <map>

using namespace std;

typedef map <string, void (*)(char*)> crmap;

struct Event
{
	int p1, p2, p3;
	int id;
	time_t time;
};

crmap init_map();
int read_args(char**);

void cmd_date(char* arg);
void cmd_time(char* arg);
void cmd_exit(char* arg);
void cmd_faster(char* arg);
void cmd_slower(char* arg);
void cmd_pause(char* arg);
void cmd_resume(char* arg);
void cmd_level(char* arg);
void cmd_stat(char* arg);