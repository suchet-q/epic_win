#pragma once

#include		<iostream>
#include		<string>
#include		<list>
#include		<fstream>
#include		<array>
#include		<map>
#include		<exception>
#include		"Clients.h"
#include		"Network.h"
#include		"Resource.h"
#include		"StructCommands.h"
#include		"Executer.h"
#include		"ResourcesChecker.h"

class			Server
{
private:
  Network		_network;
  Resource		_resources;
  Executer		_executer;
  std::array<bool, 255>		_idArray;
  std::map<entityType, t_tab_hit_box>		_tabHitBox;
  ResourcesChecker		_resourcesChecker;
public:
  Server();
  ~Server();

  bool			init(int);
  void			addClient(MetaSocket<> *);
  void			decoNotInGameClient(std::list<Client *>::iterator&);
  void			checkDecoClient(std::list<Client *> &to_deco);
  bool			loop();
};
