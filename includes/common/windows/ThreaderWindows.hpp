#pragma once
#include "WindowsInclude.h"

#define		JOIN_ERROR (-1337)

template <typename T>
int		funct(void *ptr);

template<typename T, typename S>
class ThreaderWindows
{
	int			(T::*_ptr)(S *);
	T			*_inst;
	S			*_var;
	void		*_thread;

public:
	ThreaderWindows() {}
	~ThreaderWindows() {}

	void		*getPthread() const
	{
		return this->_thread;
	}

	bool		start(int (T::*ptr)(S *), T *inst, S *var)
	{
		this->_ptr = ptr;
	    this->_inst = inst;
		this->_var = var;
		if ((this->_thread = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&funct<ThreaderWindows<T, S> >), this, 0, NULL)) == NULL)
			return false;
		return true;
	}

	int			launch()
	{
		return ((this->_inst->*_ptr)(this->_var));
	}

	int			waitThread()
	{
		if (WaitForSingleObject(this->_thread, INFINITE) == WAIT_FAILED)
			return JOIN_ERROR;
		return (1);
	}

	bool			isAlive()
	{
		if (WaitForSingleObject(this->_thread, 0) == WAIT_OBJECT_0)
			return false;
		return true;
	}

	bool		killThread()
	{
		if (TerminateThread(this->_thread, 0) == 0)
			return false;
		return true;
	}

	void		exit()
	{
		ExitThread(0);
	}
};

template<typename T>
int				funct(void *ptr)
{
	T *c = reinterpret_cast<T *>(ptr);

	return c->launch();
}
