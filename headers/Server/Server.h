#pragma once

# include		<sys/select.h>
# include		<iostream>
# include		<string>
# include		<list>
# include		<array>

# include		"Client.h"
# include		"Network.h"
# include		"Resource.h"
# include		"StructCommands.h"

class			Server
{
private:
  Network		_network;
  Resource		_resources;

public:
  Server();
  ~Server();

  bool			init(int);
  bool			loop();
};
