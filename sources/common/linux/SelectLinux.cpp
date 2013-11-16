#include		"linux/SelectLinux.h"

SelectLinux::SelectLinux(): _maxFd(0) {}

SelectLinux::~SelectLinux() {}

void		SelectLinux::fdZero(fd_set *fd)
{
  FD_ZERO(fd);
  this->_maxFd = 0;
}

void		SelectLinux::fdSet(MetaSocket<> &socket, fd_set *fd)
{
  int		fd_socket = socket.getSocket();

  FD_SET(fd_socket, fd);
  if (fd_socket > this->_maxFd)
    this->_maxFd = fd_socket;
}

bool		SelectLinux::fdIsset(MetaSocket<> &socket, fd_set *fd)
{
  if (FD_ISSET(socket.getSocket(), fd))
    return true;
  return false;
}

bool		SelectLinux::Select(fd_set *read, fd_set *write, unsigned int time)
{
  this->_timeOut.tv_sec = time / 1000000;
  this->_timeOut.tv_usec = time % 1000000;

  if (select(this->_maxFd + 1, read, write, NULL, &this->_timeOut) == -1)
    return false;
  return true;

}
