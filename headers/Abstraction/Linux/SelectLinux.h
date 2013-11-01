#pragma once

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include	"MetaSocket.h"

class		SelectLinux
{
 private:
  int		_maxFd;
  struct timeval _timeOut;

 public:
  SelectLinux();
  ~SelectLinux();
  void		fdZero(fd_set *fd);
  void		fdSet(MetaSocket<> &socket, fd_set *fd);
  bool		fdIsset(MetaSocket<> &socket, fd_set *fd);
  bool		Select(fd_set *read, fd_set *write, unsigned int time);
};
