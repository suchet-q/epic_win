#include		"Server.h"

Server::Server() {}

Server::~Server() {}

bool			Server::init(int port)
{
  if (!this->_network.initSocket(port))
    return false;
  return true;
}

bool			Server::loop()
{
	bool			error = false;

	while (!error)
	{
		this->_network.initSelect(_resources.getClients());
		if (this->_network.Select(500))
			this->_network.manageSocket(this->_resources.getClients());
		else
			error = true;
	}
	return true;
}
