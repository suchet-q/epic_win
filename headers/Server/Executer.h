#pragma once
#include "StructCommands.h"

class Executer
{
public:
	Executer();
	~Executer();
  void			execPND(void *command, int size);
  void			execNBP(void *command, int size);
  void			execNBL(void *command, int size);
  void			execJNL(void *command, int size);
  void			execCRL(void *command, int size);
  void			execPLJ(void *command, int size);
  void			execSTL(void *command, int size);
  void			execMSG(void *command, int size);
  void			execNMP(void *command, int size);
  void			execLVL(void *command, int size);
};

