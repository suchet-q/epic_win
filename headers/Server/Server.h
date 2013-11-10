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
  std::array<bool, 255>		_idArray;
  
public:
  Server();
  ~Server();

  bool			init(int);
  void			addClient(MetaSocket<> *);
//  void			decoClient(std::list<Client *>::iterator&);
  void			checkDecoClient(std::list<Client *> &to_deco);
  bool			loop();
};
