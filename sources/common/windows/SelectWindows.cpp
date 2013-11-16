#include "windows/SelectWindows.h"


SelectWindows::SelectWindows(void)
{
}


SelectWindows::~SelectWindows(void)
{
}


void		SelectWindows::fdZero(fd_set *fd)
{
	FD_ZERO(fd);
}

void		SelectWindows::fdSet(MetaSocket<> &socket, fd_set *set)
{
	FD_SET(socket.getSocket(), set);
}

bool		SelectWindows::fdIsset(MetaSocket<> &socket, fd_set *set)
{
	if (FD_ISSET(socket.getSocket(), set))
		return true;
	return false;
}

bool		SelectWindows::Select(fd_set *read, fd_set *write, unsigned int time)
{
	this->_timeOut.tv_sec = time / 1000000;
	this->_timeOut.tv_usec = time % 1000000;

	if (select(0, read, write, NULL, &this->_timeOut) == SOCKET_ERROR)
		return false;
	return true;
}
