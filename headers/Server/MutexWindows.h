#pragma once
#include <Windows.h>

class					MutexWindows
{
	CRITICAL_SECTION	_mutex;
	bool				_init;

public:
	MutexWindows(void);
	~MutexWindows(void);
	
	bool				initMutex();
	bool				Lock();
	bool				Unlock();
	bool				destroyMutex();
};

