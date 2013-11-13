#include		"Windows/MutexWindows.h"


MutexWindows::MutexWindows(void) : _init(false) {}


MutexWindows::~MutexWindows(void) {}

bool			MutexWindows::initMutex()
{
	InitializeCriticalSection(&this->_mutex);
	this->_init = true;
	return true;
}

bool			MutexWindows::Lock()
{
	if (!this->_init)
		return false;
	EnterCriticalSection(&this->_mutex);
	return true;
}

bool			MutexWindows::Unlock()
{
	if (!this->_init)
		return false;
	LeaveCriticalSection(&this->_mutex);
	return true;
}

bool			MutexWindows::destroyMutex()
{
	if (!this->_init)
		return false;
	DeleteCriticalSection(&this->_mutex);
	this->_init = false;
	return true;
}