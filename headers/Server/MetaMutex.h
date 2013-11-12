#pragma once

#ifdef _WIN32
# include "MutexWindows.h"
#else
# include "MutexLinux.h"
#endif

template<class T =
#ifdef _WIN32
	MutexWindows
#else
	MutexLinux
#endif
>
class			MetaMutex
{
	T			_mutex;

public:
	MetaMutex() {}
	~MetaMutex() {}
	bool		initMutex()
	{
		return this->_mutex.initMutex();
	}

	bool		Lock()
	{
		return this->_mutex.Lock();
	}

	bool		Unlock()
	{
		return this->_mutex.Unlock();
	}

	bool		destroyMutex()
	{
		return this->_mutex.destroyMutex();
	}
};