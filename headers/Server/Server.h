#pragma once
#include		<iostream>
#include		<string>
#include		<list>
#include		<array>

#include		"Client.h"
#include		"Network.h"
#include		"Resource.h"
#include		"StructCommands.h"
#include		"Executer.h"

class			Server
{
private:
  Network		_network;
  Resource		_resources;
  Executer		_executer;
  
public:
  Server();
  ~Server();

  bool			init(int);
  bool			loop();
};
