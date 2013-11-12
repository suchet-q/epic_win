#pragma once

#include "MetaSocket.h"

class SelectWindows
{
	struct timeval	_timeOut;

public:
	SelectWindows(void);
	~SelectWindows(void);
	void		fdZero(fd_set *fd);
	void		fdSet(MetaSocket<> &socket, fd_set *set);
	bool		fdIsset(MetaSocket<> &socket, fd_set *set);
	bool		Select(fd_set *read, fd_set *write, unsigned int time);

};

