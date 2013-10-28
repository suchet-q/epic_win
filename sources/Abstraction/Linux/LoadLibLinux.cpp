#include "Linux/LoadLibLinux.h"


LoadLibLinux::LoadLibLinux(void)
{
}


LoadLibLinux::~LoadLibLinux(void)
{
}

void		LoadLibLinux::loadLibrary(char const *name)
{
  this->_fd = dlopen(name, RTLD_LAZY);
}

void		*LoadLibLinux::getLib(char const *name)
{
  return (dlsym(this->_fd, name));
}

bool		LoadLibLinux::closeLib()
{
  if (dlclose(this->_fd) == -1)
    return (false);
  return (true);
}
