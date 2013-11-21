#pragma once
#include		"WindowsInclude.h"
#include		<iostream>
#include		<string>

class LoadLibWindows
{
 private:
  HMODULE		_modul;
 public:
  LoadLibWindows(void);
  ~LoadLibWindows(void);
  void		loadLibrary(char const *);
  void		*getLib(char const *);
  bool		closeLib();
};
