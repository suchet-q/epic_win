#include "Windows/LoadLibWindows.h"


LoadLibWindows::LoadLibWindows(void)
{
}


LoadLibWindows::~LoadLibWindows(void)
{
}

void		LoadLibWindows::loadLibrary(char const *name)
{
	this->_modul = LoadLibrary(name);
}

void		*LoadLibWindows::getLib(char const *name)
{
	return (GetProcAddress(this->_modul, name));
}

bool		LoadLibWindows::closeLib()
{
  if (!FreeLibrary(this->_modul))
    return (false);
  return (true);
}
