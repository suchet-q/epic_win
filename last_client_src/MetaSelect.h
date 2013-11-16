#pragma once

#ifdef _WIN32
# include "SelectWindows.h"
#else
# include "SelectLinux.h"
#endif

template<class T =
#ifdef _WIN32
  SelectWindows
#else
  SelectLinux
#endif
>
class		MetaSelect
{
  T		_select;

 public:
  MetaSelect() {}
  ~MetaSelect() {}
  
  void		fdZero(fd_set *fd)
  {
    this->_select.fdZero(fd);
  }

  void		fdSet(MetaSocket<> &socket, fd_set *fd)
  {
    this->_select.fdSet(socket, fd);
  }

  bool		fdIsset(MetaSocket<> &socket, fd_set *fd)
  {
    return this->_select.fdIsset(socket, fd);
  }

  bool		Select(fd_set *read, fd_set *write, unsigned int time)
  {
    return this->_select.Select(read, write, time);
  }

};
