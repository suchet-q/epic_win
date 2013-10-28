#pragma	once
#include        <dlfcn.h>
#include	<iostream>
#include	<string>

class LoadLibLinux
{
 private:
  void		*_fd;
 public:
  LoadLibLinux(void);
  ~LoadLibLinux(void);
  void		loadLibrary(char const *);
  void		*getLib(char const *);
  bool		closeLib();
};

