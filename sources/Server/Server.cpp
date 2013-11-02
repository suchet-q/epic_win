#include		"Server.h"

Server::Server() {}

Server::~Server() {}

bool			Server::init(int port)
{
  if (!_network.initSocket(port))
    return false;
  return true;
}

bool			Server::loop()
{
  bool			error = false;

  while (!error) {
    _network.initSelect(_resources.getClients());
    if (_network.Select(500))
      _network.manageSocket(_resources.getClients());
    else
      error = true;
  }
  return true;
}
