#pragma once
#include "stdafx.h"
#include "Task1.h"

double avg_interval;
CRITICAL_SECTION csexp;
exponential_distribution<double> expdist;
HANDLE event_thread;
int loggerlevel;
int event_count;

crmap init_map() {
	crmap m;
	m[string("date")] = &cmd_date;
	m[string("time")] = &cmd_time;
	m[string("exit")] = &cmd_exit;
	m[string("faster")] = &cmd_faster;
	m[string("slower")] = &cmd_slower;
	m[string("level")] = &cmd_level;
	m[string("pause")] = &cmd_pause;
	m[string("resume")] = &cmd_resume;
	m[string("stat")] = &cmd_stat;
	return m;
}

string trim(const std::string &s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

int read_args(char **argv) {
	int argc = 0;
	string args_line;

	if (!getline(cin, args_line)) {
		cout << endl;
		exit(0);
	}

	if (args_line.empty()) {
		return 0;
	}

	string trimmed_args = trim(args_line);

	char* cstr = new char[args_line.size() + 1];
	strcpy(cstr, args_line.c_str());

	char* token = strtok(cstr, " ");
	while (token != NULL) {
		argv[argc] = token;
		token = strtok(NULL, " ");
		argc++;
	}

	argv[argc] = NULL;
	return argc;
}

void cmd_date(char* arg) {
	char buffer[50];
	time_t t = time(NULL);
	tm* time = localtime(&t);
	strftime(buffer, 50, "%d.%m.%Y", time);
	cout << buffer << endl;
};

void cmd_time(char* arg) {
	char buffer[50];
	time_t t = time(NULL);
	tm* time = localtime(&t);
	strftime(buffer, 50, "%T", time);
	cout << buffer << endl;
};

void cmd_exit(char* arg){
	exit(0);
};

void cmd_faster(char* arg) {
	if (arg == NULL) {
		cerr << "No arguments" << endl;
		return;
	}
	int diff = strtol(arg, NULL, 10);
	if ((diff > 0) && (diff < avg_interval)) {
		avg_interval -= diff;
		EnterCriticalSection(&csexp);
		expdist = exponential_distribution<double>(1.0 / avg_interval);
		LeaveCriticalSection(&csexp);
	}
	else {
		cerr << "Wrong argument" << endl;
	}
};

void cmd_slower(char* arg) {
	if (arg == NULL) {
		cerr << "No arguments" << endl;
		return;
	}
	int diff = strtol(arg, NULL, 10);
	if (diff > 0) {
		avg_interval += diff;
		EnterCriticalSection(&csexp);
		expdist = exponential_distribution<double>(1.0 / avg_interval);
		LeaveCriticalSection(&csexp);
	}
	else {
		cerr << "Wrong argument" << endl;
	}
};

void cmd_pause(char* arg) {
	SuspendThread(event_thread);
};

void cmd_resume(char* arg) {
	ResumeThread(event_thread);
};

void cmd_level(char* arg) {
	if (arg == NULL) {
		cerr << "No arguments" << endl;
		return;
	}
	if (strlen(arg) > 1) {
		cerr << "Wrong argument" << endl;
	}else{
		switch (arg[0]) {
		case '0':
			loggerlevel = 0;
			break;
		case '1':
			loggerlevel = 1;
			break;
		case '2':
			loggerlevel = 2;
			break;
		default:
			cerr << "Wrong argument" << endl;
		}
	}
	return;
};

void cmd_stat(char* arg) {
	cout << "Number of events: " << event_count << endl;
};

