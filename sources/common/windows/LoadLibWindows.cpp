#include "windows/LoadLibWindows.h"


LoadLibWindows::LoadLibWindows(void)
{
}


LoadLibWindows::~LoadLibWindows(void)
{
}

void		LoadLibWindows::loadLibrary(char const *name)
{
	std::string realName(name);

	realName += ".dll";
	this->_modul = LoadLibrary(realName.c_str());
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
